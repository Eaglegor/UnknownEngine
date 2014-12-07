#include <stdafx.h>

#include <MainLoop/MainLoop.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageSender.h>
#include <Profiling/AverageFpsCounter.h>
#include <Profiling/SimpleFpsPrinter.h>
#include <Profiling/TimeCounter.h>
#include <Scalar.h>
#include <ResourceManager.h>


namespace UnknownEngine
{
	namespace Core
	{

		MainLoop::MainLoop ( UnknownEngine::Core::EngineContext* engine_context ) :
			stopped ( true ),
			engine_context(engine_context)
		{
		}

		MainLoop::~MainLoop ()
		{
			// TODO Auto-generated destructor stub
		}

		void MainLoop::start ()
		{
			stopped = false;

			Utils::TimeCounter time_counter;
			time_counter.tick();
			
			UpdateFrameMessage msg;
			
			MessageSender<UpdateFrameMessage> update_frame_message_sender(
				"Engine",
				engine_context
			);
			
			//Utils::AverageFpsCounter fps_counter(1000, Utils::SimpleFpsPrinter("MT AVG FPS: "));
			
			const Math::Scalar RESOURCES_CLEANUP_INTERVAL = 60.0f;
			Math::Scalar resources_cleanup_timer = RESOURCES_CLEANUP_INTERVAL;
						
			while ( !stopped )
			{
				time_counter.tick();
				//fps_counter.nextFrame();
				msg.dt = time_counter.getDt();
				
				resources_cleanup_timer -= msg.dt;
				if(resources_cleanup_timer < 0)
				{
					engine_context->getResourceManager()->cleanup();
					resources_cleanup_timer = RESOURCES_CLEANUP_INTERVAL;
				}
				
				update_frame_message_sender.sendMessage( msg );
			}
		}

		void MainLoop::stop()
		{
			stopped = true;
		}
		
	} /* namespace Core */
} /* namespace UnknownEngine */
