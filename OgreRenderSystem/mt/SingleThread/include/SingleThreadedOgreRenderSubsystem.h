#pragma once

#include <ThreadIndependentOgreRenderSystemBase.h>

namespace Ogre
{
	class Root;
	class SceneManager;
	class RenderWindow;
	class LogManager;
}

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}
	
	namespace Utils
	{
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreRenderCallback;

		class OgreUpdateFrameListener;

		class SingleThreadedOgreRenderSubsystem : public ThreadIndependentOgreRenderSystemBase
		{
			public:

				SingleThreadedOgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Utils::LogHelper* log_helper, Core::EngineContext* engine_context );
				
				virtual ~SingleThreadedOgreRenderSubsystem();
				
				virtual void start();
				
				virtual void stop();
		};

	} // namespace Graphics
} // namespace UnknownEngine
