/*
 * MainLoop.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <MainLoop/MainLoop.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <MessageSystem/MessageSender.h>



namespace UnknownEngine
{
	namespace Core
	{

		MainLoop::MainLoop ( UnknownEngine::Core::EngineContext* engine_context ) :
			IMessageSystemParticipant ( "Engine.MainLoop" ),
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

			current_time = ClockType::now();
			dt = dt.zero();
			
			UpdateFrameMessage msg;
			
			MessageSender<UpdateFrameMessage> update_frame_message_sender(
				MessageSystemParticipantId("Engine", MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER),
				engine_context
			);
			
			UpdateFrameMessagePacker packer ( getMessageSystemParticipantId() );
			while ( !stopped )
			{
				msg.stage = UpdateFrameMessage::PROCESSING;
				msg.dt = dt.count();
				
				update_frame_message_sender.sendMessage( msg );

				updateTime();
			}
		}

		void MainLoop::updateTime ()
		{
			ClockType::time_point temp_time = ClockType::now();
			dt = temp_time - current_time;
			current_time = temp_time;
		}

		void MainLoop::stop()
		{
			stopped = true;
		}
		
	} /* namespace Core */
} /* namespace UnknownEngine */
