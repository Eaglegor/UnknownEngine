#pragma once

#include <Descriptors/IProperty.h>
#include <Descriptors/IDescriptor.h>
#include <string>
#include <Properties/Properties.h>
#include <Descriptors/IDescriptorPropertySetter.h>
#include <Descriptors/PropertySetter.h>
#include <Descriptors/NestedDescriptorSetter.h>
#include <unordered_map>

namespace UnknownEngine
{
	namespace Utils
	{
		class Descriptor : public IDescriptor
		{
			public:
				virtual bool isValid() override
				{
					return is_valid;
				}

				IDescriptor& operator=(const Core::Properties& props) override
				{
					for(IDescriptorPropertySetter& setter : properties)
					{
						setter.parseValue(props);
						if(setter.isValid()) this->is_valid = false;
					}
					for(IDescriptorPropertySetter& setter : nested_descriptors)
					{
						setter.parseValue(props);
						if(setter.isValid()) this->is_valid = false;
					}
					return *this;
				}

				virtual operator Core::Properties()
				{
					Core::Properties props;

					for(IDescriptorPropertySetter& setter : properties)
					{
						setter.writeValue(props);
					}

					for(IDescriptorPropertySetter& setter : nested_descriptors)
					{
						setter.writeValue(props);
					}
					
					return props;
				}
			
			protected:
				void addSetter(PropertySetter &setter)
				{
					if(!setter.isValid()) this->is_valid = false;
					properties.push_back(setter);
				}
				
				void addSetter(NestedDescriptorSetter &setter)
				{
					if(!setter.isValid()) this->is_valid = false;
					nested_descriptors.push_back(setter);
				}
				
				void addSetter(PropertySetter &&setter)
				{
					if(!setter.isValid()) this->is_valid = false;
					properties.push_back(setter);
				}
				
				void addSetter(NestedDescriptorSetter &&setter)
				{
					if(!setter.isValid()) this->is_valid = false;
					nested_descriptors.push_back(setter);
				}
				
			private:
				std::vector<PropertySetter> properties;
				std::vector<NestedDescriptorSetter> nested_descriptors;
				bool is_valid;
		};
	}
}
