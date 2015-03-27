#pragma once

#include <Descriptors/IProperty.h>
#include <Descriptors/IDescriptor.h>
#include <string>
#include <Properties/Properties.h>
#include <Descriptors/IDescriptorPropertySetter.h>
#include <unordered_map>

namespace UnknownEngine
{
	namespace Utils
	{
		class Descriptor : public IDescriptor
		{
			public:
				Descriptor(std::initializer_list<IDescriptorPropertySetter> props):
				properties(props)
				{
					for(IDescriptorPropertySetter& setter : properties)
					{
						if(!setter.isValid()) this->is_valid = false;
						break;
					}
				}

				virtual bool isValid() override
				{
					return is_valid;
				}

				Descriptor& operator=(const Core::Properties& props) override
				{
					for(IDescriptorPropertySetter& setter : properties)
					{
						setter.parseValue(props);
						if(setter.isValid()) this->is_valid = false;
					}
				}

				virtual operator Core::Properties()
				{
					Core::Properties props;

					for(IDescriptorPropertySetter& setter : properties)
					{
						setter.writeValue(props);
					}

					return props;
				}

			private:
				std::vector<IDescriptorPropertySetter> properties;
				bool is_valid;
		};
	}
}
