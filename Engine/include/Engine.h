/*
 * Engine.h
 *
 *  Created on: 22 θώνÿ 2014 γ.
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

		class ComponentManager;
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
				void loadScene(const Loader::ISceneLoader* loader);

			private:
				bool init_done;

				ComponentManager* component_manager;
				MessageDispatcher* message_dispatcher;
				MessageDictionary* message_dictionary;
				PluginsManager* plugins_manager;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* ENGINE_H_ */
