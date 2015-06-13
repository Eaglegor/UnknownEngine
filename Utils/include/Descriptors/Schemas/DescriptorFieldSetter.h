#pragma once

#include <Descriptors/Schemas/IDescriptorFieldSetter.h>
#include <Descriptors/Schemas/DefaultSetters/DescriptorSetterFunction.h>
#include <Descriptors/Schemas/DescriptorSchema.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		class DescriptorFieldSetter : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<T> setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(object_schema.createDescriptor(value));
			}
			
		private:
			DescriptorSchema<T> object_schema;
			DescriptorSetterFunction<T> setter;
		};
	}
}