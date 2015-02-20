#include <stdafx.h>

#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/IComponentFactory.h>
#include <ComponentSystem/ComponentDesc.h>
#include <ComponentSystem/IComponent.h>
#include <ComponentSystem/Entity.h>
#include <ComponentSystem/EngineSpecificComponentDataImpl.h>
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

		EngineSpecificComponentDataImpl* getComponentEngineSpecificData(IComponent* component)
		{
			EngineSpecificComponentData* engine_data = component->getEngineSpecificData();
			if (engine_data != nullptr) return static_cast<EngineSpecificComponentDataImpl*>(engine_data);
			else return nullptr;
		}

		EngineSpecificComponentDataImpl* createComponentEngineSpecificData()
		{
			return new EngineSpecificComponentDataImpl();
		}

		void destroyComponentEngineSpecificData(EngineSpecificComponentData* engine_data)
		{
			delete engine_data;
		}

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

		IComponent* ComponentsManager::createComponent ( IEntity* parent, const ComponentDesc& desc ) 
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
						
						EngineSpecificComponentDataImpl* engine_data = createComponentEngineSpecificData();
						engine_data->factory_name = factory.first;
						engine_data->ref_counter = 1;
						component->setEngineSpecificData(engine_data);

						component->init(parent);
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

		void ComponentsManager::removeComponent ( IComponent* component )
		{
			LOG_INFO(logger, "Destroying component '" + std::string(component->getName()) + "'");

			EngineSpecificComponentDataImpl* engine_data = getComponentEngineSpecificData(component);

			IComponentFactory* factory;
			if (engine_data != nullptr)
			{
				LOG_DEBUG(logger, "Found engine specific data - using factory according to it");
				factory = component_factories.at(engine_data->factory_name);
			}
			else
			{
				LOG_WARNING(logger, "Not Found engine specific data - trying to find appropriate factory to destroy component");
				auto iter = std::find_if(component_factories.begin(), component_factories.end(), [&component](const std::pair<std::string, IComponentFactory*> &entry){
					if (entry.second->supportsType(component->getType())) return true;
					else return false;
				});
				if (iter != component_factories.end())
				{
					factory = iter->second;
				}
				else
				{
					LOG_ERROR(logger, "No suitable factory found to destroy component '" + std::string(component->getName()) + "'");
					return;
				}
			}
			
			LOG_DEBUG (logger, "Found factory: '" + factory->getName() );
				
			component->shutdown();

			LOG_INFO(logger, "Unregistering messaging rules for component " + std::string(component->getName()));
			MessageDispatcher::getSingleton()->clearListenerRules(component->getName());
			MessageDispatcher::getSingleton()->clearSenderRules(component->getName());
			LOG_INFO(logger, "Messaging rules for component " + std::string(component->getName()) + " unregistered");

			factory->destroyObject ( component );
			
			if (engine_data != nullptr) destroyComponentEngineSpecificData(engine_data);

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

		void Core::ComponentsManager::reserveComponent ( Core::IComponent* component )
		{
			EngineSpecificComponentDataImpl* engine_data = getComponentEngineSpecificData(component);
			if (engine_data == nullptr)
			{
				LOG_ERROR(logger, "No engine specific data found in component " + component->getName() + ". Can't reserve such component, so be careful as it may be destroyed while in use.");
				return;
			}
			++engine_data->ref_counter;
		}


		void Core::ComponentsManager::releaseComponent ( Core::IComponent* component )
		{
			EngineSpecificComponentDataImpl* engine_data = getComponentEngineSpecificData(component);
			if (engine_data == nullptr)
			{
				LOG_WARNING(logger, "No engine specific data found in component " + component->getName() + ". Reference counting isn't working - so destroying component immediately.");
				removeComponent(component);
			}
			else
			{
				if (--engine_data->ref_counter == 0)
				{
					removeComponent(component);
				}
			}
			
		}
		
	}
}

