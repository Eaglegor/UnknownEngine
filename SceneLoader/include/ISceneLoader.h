#pragma once

#include <InlineSpecification.h>

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
				ISceneLoader ( Core::EngineContext* engine_context, Core::PluginsManager* plugins_manager )
					: engine_context ( engine_context ), 
					plugins_manager ( plugins_manager )
				{
				}
				virtual ~ISceneLoader()
				{
				}

				virtual void loadScene ( const std::string &filename ) = 0;

				UNKNOWNENGINE_INLINE
				Core::EngineContext* getEngineContext()
				{
					return engine_context;
				}

				UNKNOWNENGINE_INLINE
				Core::PluginsManager* getPluginsManager()
				{
					return plugins_manager;
				}

			private:
				Core::EngineContext *engine_context;
				Core::PluginsManager* plugins_manager;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
