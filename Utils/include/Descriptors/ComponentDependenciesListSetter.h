#pragma once

#include <Descriptors/IDescriptorPropertySetter.h>
#include <Descriptors/IProperty.h>
#include <Descriptors/IComponentDependenciesList.h>
#include <ComponentSystem/IComponent.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Utils
	{
		class ComponentDependenciesListSetter : public IDescriptorPropertySetter
		{
			public:
				ComponentDependenciesListSetter(const char* name, IComponentDependenciesList &field):
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
					for(const Core::IComponent* &property: field.get())
					{
						result.push_back(property->getName());
					}
					props.set<std::vector<std::string>>(name, result);
				}

				virtual bool isValid()
				{
					return field.isValid();
				}

			private:
				IComponentDependenciesList &field;
				std::string name;
		};
	}
}
