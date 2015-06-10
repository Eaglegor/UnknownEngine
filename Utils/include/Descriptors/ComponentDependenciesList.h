#pragma once

#include <Descriptors/IProperty.h>
#include <Descriptors/IPropertiesList.h>
#include <Descriptors/IComponentDependenciesList.h>
#include <Descriptors/RequiredProperty.h>
#include <ComponentSystem/ComponentsManager.h>
#include <vector>

namespace UnknownEngine
{
	namespace Utils
	{
		template <IProperty::Optionality optionality>
		class ComponentDependenciesList : public IComponentDependenciesList
		{
			public:
				ComponentDependenciesList():
				is_explicitly_initialized(false)
				{
				}

				virtual bool isValid()
				{
					return optionality == IProperty::OPTIONAL_PROPERTY || is_explicitly_initialized;
				}

				virtual const std::vector< Core::IComponent* > & get()
				{
					return properties_list;
				}

				virtual IComponentDependenciesList &operator =(const std::vector<std::string> &props)
				{
					for(const std::string &prop : props)
					{
						properties_list.push_back(Core::ComponentsManager::findComponent(prop.c_str()));
					}
					is_explicitly_initialized = true;
				}

			private:
				bool is_explicitly_initialized;
				std::vector< Core::IComponent* > properties_list;
		};
	}
}
