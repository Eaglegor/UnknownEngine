/*
 * Engine.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <MessageSystem/IMessageSystemParticipant.h>

namespace UnknownEngine
{

	namespace Loader
	{
		class ISceneLoader;
	}

	namespace Core
	{

		class ComponentsManager;
		class MessageDispatcher;
		class MessageDictionary;
		class PluginsManager;

		class Engine : public IMessageSystemParticipant
		{
			public:
				Engine();
				virtual ~Engine();

				void init();
				void loadScene(Loader::ISceneLoader* loader);
				void start();


                MessageDispatcher *getMessageDispatcher() const;
                MessageDictionary *getMessageDictionary() const;
                ComponentsManager *getComponentsManager() const;

			private:
                bool init_done;

				void registerInternalMessageTypes();

                MessageDispatcher* message_dispatcher;
                MessageDictionary* message_dictionary;
                ComponentsManager* components_manager;
				PluginsManager* plugins_manager;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
