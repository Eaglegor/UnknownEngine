#include <stdafx.h>

#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/IComponentFactory.h>
#include <ComponentSystem/ComponentDesc.h>
#include <ComponentSystem/IComponent.h>
#include <ComponentSystem/Entity.h>
#include <ComponentSystem/EngineSpecificComponentDataImpl.h>

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
			entities_set.emplace(entity);
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
						
						bool init_success = component->init();
						if(init_success)
						{
							EngineSpecificComponentDataImpl* engine_data = createComponentEngineSpecificData();
							engine_data->factory = factory.second;
							engine_data->ref_counter = 1;
							component->setEngineSpecificData(engine_data);
						
							components.insert(std::make_pair(std::string(component->getName()), component));
						}
						else
						{
							LOG_ERROR(logger, "Failed to initialize component '" + desc.name + "'. Destroying it immediately WITHOUT a shutdown!");
							factory.second->destroyObject(component);
							component = nullptr;
						}
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
				factory = engine_data->factory;
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

			components.erase(component->getName());

			cv.notify_all();
			
			component->shutdown();

			factory->destroyObject ( component );
			
			if (engine_data != nullptr) destroyComponentEngineSpecificData(engine_data);

		}

		void ComponentsManager::removeEntity ( IEntity* entity )
		{
			if ( entity && entities_set.find(entity) != entities_set.end() )
			{
				LOG_INFO(logger, std::string("Destroying entity '") + entity->getName() + "'" );
				entity->removeAllComponents();
				entities.erase(entity->getName());
				entities_set.erase(entity);
				delete entity;
			}
		}

		void ComponentsManager::clearEntities()
		{
			for(auto &iter : entities)
			{
				LOG_INFO(logger, std::string("Destroying entity '") + iter.second->getName() + "'" );
				iter.second->removeAllComponents();
				entities_set.erase(iter.second);
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
			if(component == nullptr) {
				LOG_DEBUG(logger, "Trying to release nullptr component. Nothing to do.");
				return;
			}
			
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
		
		Core::IComponent* Core::ComponentsManager::findComponent(const char* name)
		{
			auto iter = components.find(name);
			if (iter != components.end())
			{
				return iter->second;
			}
			LOG_DEBUG(logger, "Component not found: " + name);
			return nullptr;
		}

		void ComponentsManager::waitUntilAllComponentsReleased()
		{
			std::unique_lock<LockPrimitive> guard(lock);
			const std::chrono::seconds RELEASE_WARNING_TIMEOUT(1);
			while(!components.empty())
			{
				LOG_INFO(logger, "Waiting until all components are destroyed. Remaining components: " + std::to_string(components.size()));
				std::cv_status status = cv.wait_for(guard, RELEASE_WARNING_TIMEOUT);
				if(status == std::cv_status::timeout)
				{
					LOG_WARNING(logger, "Still waiting for destruction of components. Please check if some component hasn't released it's dependencies.");
					LOG_WARNING(logger, "Unreleased components list:");
					for(auto &iter : components)
					{
						EngineSpecificComponentDataImpl* engine_data = getComponentEngineSpecificData(iter.second);
						LOG_WARNING(logger, iter.second->getName() + (engine_data != nullptr ? " (" + std::to_string(engine_data->ref_counter) + ")" : "" ) );
					}
				}
			}
		}
		
	}
}

