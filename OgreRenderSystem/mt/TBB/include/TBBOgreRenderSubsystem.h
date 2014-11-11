#pragma once

#include <functional>
#include <ThreadIndependentOgreRenderSystemBase.h>
#include <OgreRenderSubsystem_fwd.h>
#include <OgreRenderFrameListener.h>


namespace Ogre
{
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

		class TBBOgreRenderSubsystem : public ThreadIndependentOgreRenderSystemBase
		{
			public:

				TBBOgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Utils::LogHelper* log_helper, Core::EngineContext* engine_context );
				
				virtual ~TBBOgreRenderSubsystem();

				virtual void start(const std::string& name, const Core::ReceivedMessageDescriptorsList& received_messages);

				virtual void stop();

				void addSynchronizeCallback ( const std::string &name, const std::function<void() > &callback );
				
				void removeSynchronizeCallback ( const std::string& name );
				
				void addInitCallback ( const std::function<void() > &callback );
				
				void addShutdownCallback ( const std::function<void() > &callback );
				
				void addRemoveCallback ( const std::function< void() >& callback );

				UNKNOWNENGINE_INLINE
				bool hasSeparateRenderThreadEnabled()
				{
					return desc.separate_rendering_thread;
				}

			private:
				std::unique_ptr<boost::thread> rendering_thread;
				std::unique_ptr<OgreRenderFrameListener> frame_listener;
				
		};

	} // namespace Graphics
} // namespace UnknownEngine
