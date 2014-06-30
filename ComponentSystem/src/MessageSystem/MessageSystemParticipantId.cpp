#include <stdafx.h>
#include <MessageSystem/MessageSystemParticipantId.h>

namespace UnknownEngine
{
	namespace Core
	{
	
		MessageSystemParticipantId::MessageSystemParticipantId(const std::string &sender_name) :
			name(sender_name), id(INVALID_NUMERIC_IDENTIFIER)
		{
		}

		MessageSystemParticipantId::MessageSystemParticipantId(const std::string &sender_name, const NumericIdentifierType &id):
			name(sender_name), id(id)
		{
		}
		
	}
}
