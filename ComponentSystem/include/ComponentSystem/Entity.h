#pragma once

#include <ComponentSystem_export.h>
#include <unordered_map>
#include <ComponentSystem/IEntity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ILogger;

		class IComponent;
		class ComponentsManager;
		struct ComponentDesc;

		class Entity : public IEntity
		{
			public:

				Entity ( const std::string &name, ComponentsManager* components_manager );
				virtual ~Entity();
				
				virtual const char* getName() const override;

				virtual IComponent* createComponent(const ComponentDesc& desc) override;

				virtual void removeComponent ( IComponent *component ) override;
				
				virtual void removeAllComponents() override;
				
			private:
	
				typedef std::unordered_map<std::string, IComponent*> InternalMapType;

				InternalMapType components;
				std::string name;
				ComponentsManager* components_manager;
				ILogger* logger;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
