#pragma once

#include <Engine_export.h>
#include <vector>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;

		class MainLoop
		{
			public:
				ENGINE_EXPORT
				MainLoop (EngineContext* engine_context);

				ENGINE_EXPORT
				virtual ~MainLoop ();

				ENGINE_EXPORT
				void start();
				
				ENGINE_EXPORT
				void stop();
			private:
				bool stopped;

				EngineContext* engine_context;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
