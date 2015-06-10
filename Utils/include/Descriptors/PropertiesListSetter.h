#pragma once

#include <Descriptors/IDescriptorPropertySetter.h>
#include <Descriptors/IProperty.h>
#include <Descriptors/IPropertiesList.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		class PropertiesListSetter : public IDescriptorPropertySetter
		{
			public:
				PropertiesListSetter(const char* name, IPropertiesList<T> &field):
				field(field),
				name(name)
				{
				}

				virtual void parseValue(const Core::Properties &props) override{
					const std::vector<std::string>* val = props.get_pointer<std::vector<std::string>>(name);
					if(val)
					{
						field = *val;
					}
				}

				virtual void writeValue(Core::Properties &props) override
				{
					std::vector<std::string> result;
					for(const IProperty<T> &property: field.get())
					{
						result.push_back(property);
					}
					props.set<std::vector<std::string>>(name, result);
				}

				virtual bool isValid()
				{
					return field.isValid();
				}

			private:
				IPropertiesList<T> &field;
				std::string name;
		};
	}
}
