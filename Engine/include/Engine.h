/*
 * Engine.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

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

		UNKNOWNENGINE_SIMPLE_EXCEPTION(EngineNotInitializedException);

		class Engine : public IMessageSystemParticipant
		{
			public:
				Engine();
				virtual ~Engine();

				void init();
				void loadScene(Loader::ISceneLoader* loader);
				void start() throw (EngineNotInitializedException);

				EngineContext &getContext();

			private:
                bool init_done;

				void registerInternalMessageTypes();

				PluginsManager* plugins_manager;
				EngineContext context;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
