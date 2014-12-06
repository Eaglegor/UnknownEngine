/*
 * ComponentsManager.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <ComponentsManager.h>
#include <IComponentFactory.h>
#include <ComponentDesc.h>
#include <Objects/IComponent.h>
#include <algorithm>
#include <Objects/Entity.h>
#include <MessageSystem/MessageDispatcher.h>

#include <Logging.h>
#include <NameGenerators/GuidNameGenerator.h>
#include <EngineLogLevel.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		ComponentsManager* Singleton<ComponentsManager>::instance = nullptr;

		ComponentsManager::ComponentsManager() :
			internal_dictionary ( "ComponentsManager.Dictionary", NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER ),
			name_generator(new Utils::GuidNameGenerator()),
			logger(CREATE_LOGGER("Core.ComponentsManager", ENGINE_LOG_LEVEL))
		{
		}

		ComponentsManager::~ComponentsManager()
		{
			RELEASE_LOGGER(logger);
		}

		void ComponentsManager::addComponentFactory ( IComponentFactory* factory )
		{
			if ( factory->getInternalId() != INVALID_NUMERIC_IDENTIFIER ) return;

			NumericIdentifierType new_id = internal_dictionary.registerNewValue ( factory->getName() );
			factory->setInternalId ( new_id );
			component_factories.insert ( std::make_pair ( new_id, factory ) );
		}

		void ComponentsManager::removeComponentFactory ( IComponentFactory* factory )
		{
			if ( factory->getInternalId() == INVALID_NUMERIC_IDENTIFIER ) return;
			component_factories.erase ( factory->getInternalId() );
			internal_dictionary.deleteEntryByKey ( factory->getInternalId() );
			factory->setInternalId ( INVALID_NUMERIC_IDENTIFIER );
		}

		Entity *ComponentsManager::createEntity ( const std::string &name )
		{
			LOG_INFO(logger, "Creating entity: " + name );
			Entity* entity = new Entity ( name, this );
			entities.push_back ( entity );
			return entity;
		}

		IComponent* ComponentsManager::createComponent ( const ComponentDesc& desc ) 
		{
			LOG_INFO(logger, "Creating component: '" + desc.name + "' [" + desc.type + "]");
			for ( auto & factory : component_factories )
			{
				if ( factory.second->supportsType ( desc.type ) )
				{
					LOG_INFO(logger, "Found suitable factory : " + std::string(factory.second->getName()) );
					IComponent* component = factory.second->createObject ( desc );
					if(component)
					{
						LOG_INFO(logger, "Component '" + desc.name + "' created" );

						LOG_INFO(logger, "Registering messaging rules for component " + desc.name);
						MessageDispatcher::getSingleton()->setListenerRules(desc.name, desc.listener_rules);
						MessageDispatcher::getSingleton()->setSenderRules(desc.name, desc.sender_rules);
						LOG_INFO(logger, "Messaging rules for component " + desc.name + " registered");
					}
					else
					{
						LOG_ERROR (logger, "Component '" + desc.name + "' was NOT created" );
					}
					return component;
				}
			}
			LOG_ERROR (logger, "Not found factory for component type: '" + desc.type + "'" );
			return nullptr;
			//throw NoSuitableFactoryFoundException ( "Can't find factory for component" );
		}

		void ComponentsManager::removeComponent ( IComponent *component )
		{
			LOG_INFO(logger, "Destroying component '" + std::string(component->getName()) + "'" );
			for ( auto & factory : component_factories )
			{
				if ( factory.second->supportsType ( component->getType() ) )
				{
					LOG_INFO(logger, "Unregistering messaging rules for component " + std::string(component->getName()));
					MessageDispatcher::getSingleton()->clearListenerRules(MessageSystemParticipantId(component->getName()));
					MessageDispatcher::getSingleton()->clearSenderRules(MessageSystemParticipantId(component->getName()));
					LOG_INFO(logger, "Messaging rules for component " + std::string(component->getName()) + " unregistered");

					factory.second->destroyObject ( component );
					return;
				}
			}
			LOG_ERROR (logger, "No suitable factory found to destroy component '" + std::string(component->getName()) + "'" );
			throw NoSuitableFactoryFoundException ( "Can't find factory able to destroy component" );
		}

		void ComponentsManager::removeEntity ( Entity* entity )
		{
			if ( entity )
			{
				entity->removeAllComponents();
				LOG_INFO(logger, "Destroying entity '" + entity->getName() + "'" );
				auto iter = std::find ( entities.begin(), entities.end(), entity );
				if ( iter != entities.end() ) *iter = nullptr;
				delete entity;
			}
		}

		void ComponentsManager::clearEntities()
		{
			for ( Entity * entity : entities )
			{
				removeEntity ( entity );
			}
		}

		Utils::NameGenerator* ComponentsManager::getNameGenerator()
		{
			return name_generator.get();
		}
		
	} /* namespace Core */
} /* namespace UnknownEngine */

