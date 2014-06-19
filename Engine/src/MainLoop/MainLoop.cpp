/*
 * MainLoop.cpp
 *
 *  Created on: 17 ���� 2014 �.
 *      Author: gorbachenko
 */

#include <time.h>

#include <MainLoop/MainLoop.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Core
	{

		MainLoop::MainLoop ()
		{
			// TODO Auto-generated constructor stub

		}

		MainLoop::~MainLoop ()
		{
			// TODO Auto-generated destructor stub
		}

		void MainLoop::start ()
		{
			current_time = clock() / static_cast<float>(CLOCKS_PER_SEC);
			UpdateFrameMessage msg;
			UpdateFrameMessagePacker packer("Internal.MainLoop");
			while ( true )
			{
				msg.stage = UpdateFrameMessage::PREPROCESSING;
				msg.dt = dt;
				MessageDispatcher::getSingleton()->deliverMessage(packer.packMessage(msg));

				msg.stage = UpdateFrameMessage::PROCESSING;
				msg.dt = dt;
				MessageDispatcher::getSingleton()->deliverMessage(packer.packMessage(msg));

				updateTime();

				msg.stage = UpdateFrameMessage::POSTPROCESSING;
				msg.dt = dt;
				MessageDispatcher::getSingleton()->deliverMessage(packer.packMessage(msg));
			}
		}

		void MainLoop::updateTime ()
		{
			float temp_time = clock() / static_cast<float>(CLOCKS_PER_SEC);
			dt = temp_time - current_time;
			current_time = temp_time;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */