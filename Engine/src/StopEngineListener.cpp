#include <stdafx.h>
#include <StopEngineListener.h>
#include <MainLoop/MainLoop.h>
#include <MessageSystem/PackedMessage.h>

UnknownEngine::Core::StopEngineListener::StopEngineListener ( const std::string name, MainLoop* main_loop )
	: IMessageListener ( name ),
	  main_loop ( main_loop )
{}

void UnknownEngine::Core::StopEngineListener::processMessage ( const PackedMessage &msg )
{
	if ( msg.getMessageTypeId() == MessageDictionary::getSingleton()->getMessageTypeId ( StopEngineActionMessage::getTypeName() ) )
	{
		main_loop->stop();
	}
}
