/*
 * Engine.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#ifndef ENGINE_H_
#define ENGINE_H_

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

		class Engine
		{
			public:
				Engine();
				virtual ~Engine();

				void start();
				void init();
				void loadScene(Loader::ISceneLoader* loader);


                MessageDispatcher *getMessageDispatcher() const;
                MessageDictionary *getMessageDictionary() const;
                ComponentsManager *getComponentsManager() const;

        private:
                bool init_done;

                MessageDispatcher* message_dispatcher;
                MessageDictionary* message_dictionary;
                ComponentsManager* components_manager;
				PluginsManager* plugins_manager;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* ENGINE_H_ */
