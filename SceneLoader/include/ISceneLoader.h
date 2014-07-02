/*
 * ISceneLoader.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#ifndef ISCENELOADER_H_
#define ISCENELOADER_H_

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class PluginsManager;
	}

	namespace Loader
	{

		class ISceneLoader
		{
			public:
				ISceneLoader()
				{
				}
				virtual ~ISceneLoader()
				{
				}

				virtual void loadScene(Core::EngineContext *engine_context, Core::PluginsManager* plugins_manager) = 0;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* ISCENELOADER_H_ */
