/*
 * ISceneLoader.h
 *
 *  Created on: 22 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#ifndef ISCENELOADER_H_
#define ISCENELOADER_H_

namespace UnknownEngine
{
	namespace Core
	{
		class ComponentsManager;
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

				virtual void loadScene(Core::ComponentsManager *components_manager, Core::PluginsManager* plugins_manager) = 0;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* ISCENELOADER_H_ */
