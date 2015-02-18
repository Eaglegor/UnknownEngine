#include <stdafx.h>

#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/IComponentFactory.h>
#include <ComponentSystem/ComponentDesc.h>
#include <ComponentSystem/IComponent.h>
#include <ComponentSystem/Entity.h>
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
			auto iter = component_factories.find(std::string(factory->getName()));
			if(iter != component_factories.end()) {
				LOG_ERROR(logger, std::string("Failed to register component factory ") + factory->getName() + ". Factory with the same name alreadt registered");
				return;
			}
			component_factories.emplace(std::string(factory->getName()), factory);
		}

		void ComponentsManager::removeComponentFactory ( IComponentFactory* factory )
		{
			auto iter = component_factories.find(std::string(factory->getName()));
			if(iter == component_factories.end()) 
			{
				LOG_ERROR(logger, std::string("Can't remove component factory ") + factory->getName() + ". Factory not registered");
				return;
			}
			component_factories.erase ( iter );
		}

		IEntity *ComponentsManager::createEntity ( const std::string &name )
		{
			auto iter = entities.find(name);
			if(iter != entities.end())
			{
				LOG_ERROR(logger, "Failed to create entity " + name + ". Entity with the same name already exists");
				return nullptr;
			}
			LOG_INFO(logger, "Creating entity: " + name );
			IEntity* entity = new Entity ( name, this );
			entities.emplace(name, entity);
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
						MessageDispatcher::getSingleton()->setListenerRules(desc.name.c_str(), desc.listener_rules);
						MessageDispatcher::getSingleton()->setSenderRules(desc.name.c_str(), desc.sender_rules);
						LOG_INFO(logger, "Messaging rules for component " + desc.name + " registered");
						
						ComponentWrapper wrapper;
						wrapper.component = component;
						wrapper.factory_name = factory.second->getName();
						components.insert( std::make_pair(desc.name, wrapper) );
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
		}

		void ComponentsManager::removeComponent ( std::unordered_map<std::string, ComponentWrapper>::iterator iter )
		{
			IComponent *component = iter->second.component;
			LOG_INFO(logger, "Destroying component '" + std::string(component->getName()) + "'" );
			
			auto factory_iter = component_factories.find(iter->second.factory_name);
			
			if(factory_iter != component_factories.end())
			{
				LOG_INFO(logger, "Unregistering messaging rules for component " + std::string(component->getName()));
				MessageDispatcher::getSingleton()->clearListenerRules(component->getName());
				MessageDispatcher::getSingleton()->clearSenderRules(component->getName());
				LOG_INFO(logger, "Messaging rules for component " + std::string(component->getName()) + " unregistered");

				factory_iter->second->destroyObject ( component );
			
				components.erase(iter);
				return;
			}
			LOG_ERROR (logger, "No suitable factory found to destroy component '" + std::string(component->getName()) + "'" );
		}

		void ComponentsManager::removeEntity ( IEntity* entity )
		{
			if ( entity )
			{
				LOG_INFO(logger, std::string("Destroying entity '") + entity->getName() + "'" );
				entity->removeAllComponents();
				entities.erase(entity->getName());
				delete entity;
			}
		}

		void ComponentsManager::clearEntities()
		{
			for(auto &iter : entities)
			{
				LOG_INFO(logger, std::string("Destroying entity '") + iter.second->getName() + "'" );
				iter.second->removeAllComponents();
				delete iter.second;
			}
			entities.clear();
		}

		Utils::NameGenerator* ComponentsManager::getNameGenerator()
		{
			return name_generator.get();
		}
		
		Core::IComponent* Core::ComponentsManager::findComponent ( const char* name )
		{
			auto iter = components.find(name);
			if(iter == components.end()) return nullptr;
			return iter->second.component;
		}

		void Core::ComponentsManager::reserveComponent ( Core::IComponent* component )
		{
			auto iter = components.find(component->getName());
			if(iter == components.end())
			{
				LOG_ERROR(logger, "Can't reserve unknown component " + component->getName());
				return;
			}
			++iter->second.ref_counter;
		}

		void Core::ComponentsManager::releaseComponent ( Core::IComponent* component )
		{
			auto iter = components.find(component->getName());
			if(iter == components.end())
			{
				LOG_ERROR(logger, "Can't release unknown component " + component->getName());
				return;
			}
			if(--iter->second.ref_counter == 0)
			{
				removeComponent(iter);
			}
		}
		
	}
}

