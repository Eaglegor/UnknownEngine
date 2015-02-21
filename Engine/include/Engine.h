#pragma once

#include <Engine_export.h>
#include <Exception.h>
#include <EngineContext.h>
#include <memory>

namespace UnknownEngine
{

	namespace Loader
	{
		class ISceneLoader;
	}

	namespace Core
	{

		class MainLoopComponent;

		class MainLoopComponentFactory;

		class ConsoleLoggingSubsystem;

		class ILogger;

		class PluginsManager;
		class IEntity;

		UNKNOWNENGINE_SIMPLE_EXCEPTION ( InvalidEngineStateException );

		static const char* MAIN_LOOP_COMPONENT_NAME = "Engine.MainLoop";
		
		class Engine
		{
			public:

				ENGINE_EXPORT
				Engine();

				ENGINE_EXPORT
				virtual ~Engine();

				ENGINE_EXPORT
				void init() ;

				ENGINE_EXPORT
				void start() ;

				ENGINE_EXPORT
				void stop() ;

				ENGINE_EXPORT
				void shutdown() ;

				ENGINE_EXPORT
				EngineContext &getContext();

				ENGINE_EXPORT
				PluginsManager *getPluginsManager();

			private:
				enum State
				{
				    CREATED = 0,
				    INIT = 1,
				    STARTED = 2,
				    STOPPED = 3
				};

				void initMessagingRules(const std::string &name);
				
				State state;

				std::unique_ptr<MainLoopComponentFactory> main_loop_factory;
				IEntity* engine_entity;
				MainLoopComponent* main_loop;
				PluginsManager* plugins_manager;
				EngineContext context;
				std::unique_ptr<ConsoleLoggingSubsystem> console_logging_subsystem;
				ILogger* logger = nullptr;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
