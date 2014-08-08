#pragma once

#include <Engine_export.h>
#include <Engine.h>
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

		UNKNOWNENGINE_SIMPLE_EXCEPTION ( InvalidEngineStateException ); ///< Is thrown if trying to perform action not suitable for current state

		/**

		\brief A class binding all core subsystems together

		### Concept
		The main purpose of Engine class is to provide a simple interface in terms of init/start.

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

		###Notes
		Engine can't inherit from IMessageSystemParticipantId because at the moment of it's creation there is still
		no message system participant dictionary created. That's why the engine initializes it's address later.

		*/

		class Engine
		{
			public:
				/**
				 *  @brief Default constructor. **Doesn't init anything**.
				 */
				ENGINE_EXPORT
				Engine();

				ENGINE_EXPORT
				virtual ~Engine();

				/**
				 * @brief Inits engine
				 *
				 * - Creates core subsystems
				 * - Inits \ref UnknownEngine::Core::EngineContext "engine context"
				 * - Registers core message types
				 *
				 * @throws UnknownEngine::Core::InvalidEngineStateException - Is thrown after double initialization
				 */
				ENGINE_EXPORT
				void init() throw ( InvalidEngineStateException );

				/**
				 * @brief Starts engine
				 *
				 * Creates and starts the main loop in the context of calling thread.
				 * It doesn't return until the main loop is broken.
				 *
				 * @throw UnknownEngine::Core::InvalidEngineStateException - Is thrown if starting uninitialized engine
				 */
				ENGINE_EXPORT
				void start() throw ( InvalidEngineStateException );

				/**
				 * @brief Shutdowns engine
				 *
				 * Deletes context. Resets init status.
				 *
				 * @throw UnknownEngine::Core::InvalidEngineStateException - Is thrown if shutting down engine before it's stop
				 */
				ENGINE_EXPORT
				void shutdown() throw ( InvalidEngineStateException );

				/**
				 * @brief Returns engine context
				 * @return %Engine context
				 */
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

				State state;

				void registerInternalMessageTypes(); ///< Registers all internal message types
				MessageSystemParticipantId message_system_participant_id;
				PluginsManager* plugins_manager; ///< Plugins manager instance. Isn't a part of context
				EngineContext context; ///< Engine context
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
