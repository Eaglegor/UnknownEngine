#include <stdafx.h>
#include <StopEngineListener.h>
#include <MainLoop/MainLoop.h>
#include <MessageSystem/PackedMessage.h>

namespace UnknownEngine
{
	namespace Core
	{
		StopEngineListener::StopEngineListener ( const std::string name, MainLoop* main_loop ):
		name(name),
		main_loop(main_loop)
		{}

		void StopEngineListener::processMessage ( const PackedMessage &msg )
		{
			if ( msg.getMessageTypeId() == MessageDictionary::getSingleton()->getMessageTypeId ( StopEngineActionMessage::getTypeName() ) )
			{
				main_loop->stop();
			}
		}
		
		const char* StopEngineListener::getName() const
		{
			return name.c_str();
		}

	}
}


