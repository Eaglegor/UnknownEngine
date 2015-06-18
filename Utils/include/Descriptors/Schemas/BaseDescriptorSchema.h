#pragma once

#include <Descriptors/Schemas/IDescriptorSchema.h>
#include <Descriptors/Schemas/DescriptorField.h>
#include <Descriptors/Schemas/Implementations/Common/DefaultDescriptorFieldSetters.h>
#include <Descriptors/Schemas/DescriptorSettersFactory.h>
#include <unordered_map>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		class BaseDescriptorSchema : public IDescriptorSchema<T>
		{
		public:
			virtual void fillDescriptorFromPropertiesTree(const PropertiesTreeNode &properties, T& out_desc)
			{
				for(auto &iter : fields)
				{
					DescriptorField<T>& field = iter.second;
					PropertiesTreeNode* node = properties.getChild(iter.first.c_str());
					if(!field.is_optional && node == nullptr)
					{
						throw std::logic_error("Required descriptor field " + iter.first + " is not found");
					}
					if(node != nullptr)
					{
						IDescriptorFieldSetter* setter = field.setters_factory->createSetter(out_desc);
						setter->setValue(*node);
						field.setters_factory->destroySetter(setter);
					}
				}
			}
			
			virtual T createDefaultDescriptor()
			{
				return T();
			}
			
			virtual T createDescriptor(const PropertiesTreeNode &properties)
			{
				T desc = createDefaultDescriptor();
				fillDescriptorFromPropertiesTree(properties, desc);
				return desc;
			}
			
			virtual PropertiesTreeNode convertDescriptorToPropertiesTree(const T& descriptor)
			{
				PropertiesTreeNode tree;
				writeDescriptorToPropertiesTree(descriptor, tree);
				return tree;
			}
			
			virtual void writeDescriptorToPropertiesTree(const T& descriptor, PropertiesTreeNode &out_properties)
			{
				
			}
			
			virtual bool descriptorIsValid(const T& desc)
			{
				return true;
			}

		protected:
			template<typename V>
			void addField(const char* name, RawDescriptorSetterFunction<T, V> setter_function, bool is_optional)
			{
				DescriptorField<T> field;
				field.is_optional = is_optional;
				field.setters_factory = std::make_shared<DescriptorSettersFactory <T, V> >(setter_function);
				fields.emplace(name, field);
			}
			
			template<typename V>
			void addOptionalField(const char* name, RawDescriptorSetterFunction<T, V> setter_function)
			{
				addField(name, setter_function, true);
			}

			template<typename V>
			void addRequiredField(const char* name, RawDescriptorSetterFunction<T, V> setter_function)
			{
				addField(name, setter_function, false);
			}
			
		private:
			std::unordered_map<std::string, DescriptorField<T> > fields;
			
		};
	}
}
