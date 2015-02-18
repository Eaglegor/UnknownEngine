#include <stdafx.h>

#include <ComponentSystem/Entity.h>
#include <ComponentSystem/IComponent.h>
#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/ComponentDesc.h>

#include <Logging.h>
#include <EngineLogLevel.h>

namespace UnknownEngine
{
	namespace Core
	{

		Entity::Entity ( const std::string &name, ComponentsManager* components_manager ) :
			name ( name ),
			components_manager ( components_manager ),
			logger ( CREATE_LOGGER ( std::string ( "(Entity) " ) + name.c_str(), ENGINE_LOG_LEVEL ) )
		{
		}

		Entity::~Entity ()
		{
			RELEASE_LOGGER ( logger );
		}

		IComponent* Entity::createComponent ( const ComponentDesc& desc )
		{
			if ( components.find ( desc.name ) != components.end() )
			{
				LOG_ERROR ( logger, std::string ( "Component with the name " ) + desc.name + " already exists. New component wasn't created." );
				return nullptr;
			}
			LOG_INFO ( logger, "Creating component '" + desc.name + "'" );
			IComponent* component = components_manager->createComponent ( this, desc );
			if ( component == nullptr )
			{
				LOG_ERROR ( logger, std::string ( "Failed to create component " ) + desc.name );
				return nullptr;
			}
			components.emplace ( desc.name, component );
			return component;
		}

		void Entity::removeAllComponents()
		{
			for ( auto & iter : components )
			{
				components_manager->releaseComponent ( iter.second );
			}
			components.clear();
		}

		void Entity::removeComponent ( IComponent *component )
		{
			if ( component == nullptr )
			{
				LOG_WARNING ( logger, "Trying to delete nullptr component. Nothing is to be done." );
				return;
			}
			if ( components.find ( std::string ( component->getName() ) ) != components.end() )
			{
				LOG_ERROR ( logger, std::string ( "Component " ) + component->getName() + " isn't a part of entity " + getName() + " so it wasn't deleted" );
				return;
			}
			components.erase ( name );
			component->shutdown();
			components_manager->releaseComponent ( component );
		}

		const char* Entity::getName() const
		{
			return name.c_str();
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
