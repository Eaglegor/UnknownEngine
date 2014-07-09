#pragma once

#include <MessageSystem/IMessageSystemParticipant.h>
#include <Exception.h>
#include <EngineContext.h>

namespace UnknownEngine
{

	namespace Loader
	{
		class ISceneLoader;
	}

	namespace Core
	{

		class PluginsManager;

		UNKNOWNENGINE_SIMPLE_EXCEPTION(EngineNotInitializedException); ///< Is thrown if Engine is started without initialization
		UNKNOWNENGINE_SIMPLE_EXCEPTION(EngineAlreadyInitializedException); ///< Is thrown if Engine is initialized twice

		/**

		\brief A class binding all core subsystems together

		### Concept
		The main purpose of Engine class is to provide a simple interface in terms of init/start.
		The engine can send messages to subsystems, so it inherits from \ref UnknownEngine::Core::IMessageSystemParticipant "IMessageSystemParticipant".

		### Usage
		When you want to use Unknown %Engine you create the instance of Engine class. It's not initialized yet that's why you must call init() method.
		After that you can call start() method to start a main loop of engine.
		
		#### Example
		\code
		
			#include <Engine.h>
			#include <XmlSceneLoader.h>

			using namespace UnknownEngine;
			
			int main()
			{
			  Loader::XmlSceneLoader loader("SceneFile.xml");

			  Core::Engine engine;
			  engine.init();
			  engine.loadScene(&loader);
			  engine.start();

			  return 0;
			}
		
		\endcode
		
		*/

		class Engine : public IMessageSystemParticipant
		{
			public:
				/**
				 *  @brief Default constructor. **Doesn't init anything**.
				 */
				Engine();
				virtual ~Engine();

				/**
				 * @brief Inits engine
				 * 
				 * - Creates core subsystems
				 * - Inits \ref UnknownEngine::Core::EngineContext "engine context"
				 * - Registers core message types
				 *
				 * @throws UnknownEngine::Core::EngineAlreadyInitializedException - Is thrown after double initialization
				 */
				void init() throw(EngineAlreadyInitializedException);

				/**
				 * @brief Loads scene using provided loader
				 * @param loader - %Scene loader implementation
				 */
				void loadScene(Loader::ISceneLoader* loader);

				/**
				 * @brief Starts engine
				 *
				 * Creates and starts the main loop in the context of calling thread.
				 * It doesn't return until the main loop is broken.
				 *
				 * @throw UnknownEngine::Core::EngineNotInitializedException - Is thrown if starting uninitialized engine
				 */
				void start() throw (EngineNotInitializedException);

				/**
				 * @brief Returns engine context
				 * @return %Engine context
				 */
				EngineContext &getContext();

			private:
				bool init_done; ///< Flag indicating that initialization is done

				void registerInternalMessageTypes(); ///< Registers all internal message types

				PluginsManager* plugins_manager; ///< Plugins manager instance. Isn't a part of context
				EngineContext context; ///< Engine context
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
