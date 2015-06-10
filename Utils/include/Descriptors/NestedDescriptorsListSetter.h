#pragma once

#include <Descriptors/IDescriptorPropertySetter.h>
#include <Descriptors/IProperty.h>
#include <Descriptors/IDescriptorsList.h>
#include <Descriptors/IDescriptor.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Utils
	{
		class NestedDescriptorsListSetter : public IDescriptorPropertySetter
		{
			public:
				NestedDescriptorsListSetter(const char* name, IDescriptorsList &field):
				field(field),
				name(name)
				{
				}

				virtual void parseValue(const Core::Properties &props) override{
					const std::vector<Core::Properties>* val = props.get_pointer<std::vector<Core::Properties>>(name);
					if(val)
					{
						field = *val;
					}
				}

				virtual void writeValue(Core::Properties &props) override
				{
					std::vector<Core::Properties> result;
					for(const IDescriptor &property: field.get())
					{
						result.push_back(property);
					}
					props.set<std::vector<Core::Properties>>(name, result);
				}

				virtual bool isValid()
				{
					return field.isValid();
				}

			private:
				IDescriptorsList &field;
				std::string name;
		};
	}
}
