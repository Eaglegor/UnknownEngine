#include <stdafx.h>

#include <MessageSystem/IMessageSystemParticipant.h>
#include <MessageSystem/MessageSystemParticipantDictionary.h>
#include <iostream>
namespace UnknownEngine
{
	namespace Core
	{

		IMessageSystemParticipant::IMessageSystemParticipant ( const std::string &object_name ):
		message_system_participant_id(object_name, MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER)
		{
		}

		IMessageSystemParticipant::~IMessageSystemParticipant()
		{
		}

	} // namespace Core
} // namespace UnknownEngine
