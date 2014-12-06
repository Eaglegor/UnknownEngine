#pragma once

#include <ComponentSystem_export.h>
#include <InlineSpecification.h>
#include <unordered_map>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		class ILogger;

		class IComponent;
		class ComponentsManager;
		struct ComponentDesc;

		UNKNOWNENGINE_SIMPLE_EXCEPTION ( DuplicateComponentNameException );
		UNKNOWNENGINE_SIMPLE_EXCEPTION ( ComponentNotFoundException );

		class Entity
		{
			public:

				COMPONENTSYSTEM_EXPORT
				Entity ( const std::string &name, ComponentsManager* components_manager );

				COMPONENTSYSTEM_EXPORT
				virtual ~Entity ();

				COMPONENTSYSTEM_EXPORT
				std::string getName() const;

				COMPONENTSYSTEM_EXPORT
				IComponent* createComponent(const ComponentDesc& desc);

				COMPONENTSYSTEM_EXPORT
				void removeComponent ( IComponent *component );
				
				COMPONENTSYSTEM_EXPORT
				void removeAllComponents();
				
			private:
	
				typedef std::unordered_map<std::string, IComponent*> InternalMapType;

				InternalMapType components;
				std::string name;
				ComponentsManager* components_manager;
				ILogger* logger;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
