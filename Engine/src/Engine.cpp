#include <stdafx.h>

#include <Engine.h>
#include <MainLoop/MainLoopComponent.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageDictionary.h>
#include <ResourceManager/ResourceManager.h>
#include <Plugins/PluginsManager.h>
#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/ComponentDesc.h>
#include <ComponentSystem/Entity.h>


#include <Plugins/SubsystemDesc.h>
#include <ISceneLoader.h>

#include <Logging/ConsoleLoggingSubsystem.h>

#include <LogManager.h>
#include <Logging.h>
#include <EngineLogLevel.h>
#include <MainLoopComponentFactory.h>
#include <EngineStarterComponent.h>

namespace UnknownEngine
{
	namespace Core
	{

		Engine::Engine() :
			state ( CREATED ),
			console_logging_subsystem ( new ConsoleLoggingSubsystem ( "ConsoleLoggingSubsystem" ) )
		{
			LOG_INFO ( logger, "Engine created" );
		}

		Engine::~Engine()
		{
		}

		void Engine::start()
		{

			LOG_INFO ( logger, "Starting engine" );

			if ( state == CREATED ) throw InvalidEngineStateException ( "Engine wasn't initialized. Please call Engine::init() prior to Engine::start()" );
			if ( state == STARTED ) throw InvalidEngineStateException ( "Can't start the engine twice" );

			state = STARTED;
			
			if ( main_loop )
			{
				LOG_INFO ( logger, "Starting main loop" );
				main_loop->start();
			}

			state = STOPPED;

		}

		void Engine::stop()
		{
			LOG_INFO ( logger, "Stopping engine" );
			if(main_loop) main_loop->stop();
		}

		void Engine::shutdown()
		{

			LOG_INFO ( logger, "Shutting down engine" );

			if ( state == STARTED ) throw InvalidEngineStateException ( "Shutting down running engine is not allowed" );
			if ( state == CREATED ) throw InvalidEngineStateException ( "Shutting down uninitialized engine is not allowed" );

			LOG_INFO ( logger, "Destroying remaining entities" );

			this->context.components_manager->clearEntities();

			this->context.resource_manager->waitUntilAllDataProvidersReleased();
			this->context.components_manager->waitUntilAllComponentsReleased();
			
			LOG_INFO ( logger, "Destroying plugins manager" );
			PluginsManager::destroyInstance();

			context.getComponentsManager()->removeComponentFactory ( main_loop_factory.get() );
			main_loop_factory.reset();
			
			LOG_INFO ( logger, "Destroying components manager" );
			ComponentsManager::destroyInstance();
			
			LOG_INFO ( logger, "Destroying messaging policies dictionary" );
			MessagingPoliciesManager::destroyInstance();

			LOG_INFO ( logger, "Destroying resource manager" );
			ResourceManager::destroyInstance();

			LOG_INFO ( logger, "Destroying message dispatcher" );
			MessageDispatcher::destroyInstance();

			LOG_INFO ( logger, "Destroying message dictionary" );
			MessageDictionary::destroyInstance();

			LOG_INFO ( logger, "Engine shutdown complete" );

			RELEASE_LOGGER ( logger );
			context.log_manager->removeLoggingSubsystem ( console_logging_subsystem.get() );
			LogManager::destroyInstance();

			state = CREATED;
		}

		EngineContext& Engine::getContext()
		{
			return context;
		}

		void Engine::init()
		{
			context.log_manager = LogManager::createInstance();
			context.log_manager->addLoggingSubsystem ( console_logging_subsystem.get() );
			logger = CREATE_LOGGER ( "Engine", ENGINE_LOG_LEVEL );

			LOG_INFO ( logger, "Initializing engine" );

			if ( state == INIT ) throw InvalidEngineStateException ( "Double engine initialization is not allowed" );
			if ( state == STARTED ) throw InvalidEngineStateException ( "Running engine initialization is not allowed" );
			if ( state == STOPPED ) throw InvalidEngineStateException ( "Stopped engine initialization is not allowed. Call shutdown() prior." );

			LOG_INFO ( logger, "Creating message dictionary" );
			MessageDictionary::createInstance();

			LOG_INFO ( logger, "Creating message dispatcher" );
			context.message_dispatcher = MessageDispatcher::createInstance();

			LOG_INFO ( logger, "Creating components manager" );
			context.components_manager = ComponentsManager::createInstance();

			LOG_INFO ( logger, "Creating messaging policies dictionary" );
			MessagingPoliciesManager::createInstance();

			LOG_INFO ( logger, "Creating resource manager" );
			context.resource_manager = ResourceManager::createInstance();

			LOG_INFO ( logger, "Creating plugins manager" );
			plugins_manager = PluginsManager::createInstance ( &context );

			state = INIT;

			main_loop_factory.reset ( new EngineCoreComponentsFactory(*this) );
			context.getComponentsManager()->addComponentFactory ( main_loop_factory.get() );
			engine_entity = context.getComponentsManager()->createEntity ( "Engine" );
			
			
			main_loop = nullptr;
			{
				ComponentDesc desc;
				desc.type = MainLoopComponent::getTypeName();
				desc.name = MAIN_LOOP_COMPONENT_NAME;
				
				IComponent* component = engine_entity->createComponent ( desc );
				if ( !component )
				{
					LOG_ERROR ( logger, "Can't create main loop component" );
				}
				else
				{
					main_loop = static_cast<MainLoopComponent*> ( component );
				}
			}

            engine_starter = nullptr;
            {
                ComponentDesc desc;
                desc.type = EngineStarterComponent::getTypeName();
                desc.name = ENGINE_STARTER_COMPONENT_NAME;

                IComponent* component = engine_entity->createComponent ( desc );
                if ( !component )
                {
                    LOG_ERROR ( logger, "Can't create engine starter component" );
                }
                else
                {
                    engine_starter = static_cast<EngineStarterComponent*> ( component );
                }
            }

		}

		PluginsManager* Engine::getPluginsManager()
		{
			return plugins_manager;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
