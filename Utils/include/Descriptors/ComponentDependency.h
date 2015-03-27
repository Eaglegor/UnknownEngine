#pragma once

#include <Descriptors/IProperty.h>
#include <boost/lexical_cast.hpp>
#include <string>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Utils
	{
                template<IProperty::Optionality optionality>
                class ComponentDependency : public IProperty
		{
			public:
                                ComponentDependency(){}
                                ComponentDependency(Core::IComponent* component):component(component){}

                                operator Core::IComponent*()
				{
                                        return component;
				}

				virtual IProperty& operator =(const char *string_value_representation) override
				{
                                    component = Core::ComponentsManager::getSingleton()->findComponent(string_value_representation);
                                    return *this;
				}

				virtual operator std::string() override
				{
                                        return component->getName();
				}

				virtual bool isValid()
				{
                                        if(component) return true;
                                        return false;
				}

			private:
                                Core::IComponent* component;
		};
	}
}
