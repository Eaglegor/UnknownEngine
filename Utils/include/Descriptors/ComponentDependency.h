#pragma once

#include <Descriptors/IProperty.h>
#include <boost/lexical_cast.hpp>
#include <string>
#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/IComponent.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<IProperty::Optionality optionality>
		class ComponentDependency : public IProperty
		{
			public:
				ComponentDependency() : component(nullptr) {}
				ComponentDependency ( Core::IComponent* component ) : component ( component ) {}

				operator Core::IComponent*() const
				{
					return component;
				}

				virtual ComponentDependency<optionality>& operator = ( Core::IComponent* component )
				{
					this->component = component;
					return *this;
				}
				
				virtual IProperty& operator = ( const std::string &string_value_representation ) override
				{
					component = Core::ComponentsManager::getSingleton()->findComponent ( string_value_representation.c_str() );
					return *this;
				}

				virtual operator std::string() override
				{
					return component->getName();
				}

				virtual bool isValid()
				{
					if ( component ) return true;
					return optionality == REQUIRED ? false : true;
				}
				
				virtual Core::IComponent* operator->()
				{
					return component;
				}

			private:
				Core::IComponent* component;
		};
	}
}
