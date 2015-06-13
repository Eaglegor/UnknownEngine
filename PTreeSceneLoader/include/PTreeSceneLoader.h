#pragma once

#include <string>

#include <EntitiesLoader.h>
#include <ConstantsHolder.h>
#include <PTreeSceneLoader_export.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}

	namespace Loader
	{
		class PTreeSceneLoader
		{
			public:
				PTREESCENELOADER_EXPORT
				void loadScene(const char* filename);
				
			private:
				EntitiesLoader loader;
				ConstantsHolder constants_holder;
		};
	} /* namespace Loader */
} /* namespace UnknownEngine */
