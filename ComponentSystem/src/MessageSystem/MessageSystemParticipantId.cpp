#include <stdafx.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <MessageSystem/MessageSystemParticipantDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		MessageSystemParticipantId::MessageSystemParticipantId ( const std::string &object_name ) :
			name ( object_name ),
			id ( MessageSystemParticipantDictionary::getSingleton()->getMessageParticipantNameId ( object_name ) )
		{

		}

		MessageSystemParticipantId::MessageSystemParticipantId() :
			name ( "" ),
			id ( INVALID_NUMERIC_IDENTIFIER )
		{
		}

		MessageSystemParticipantId::MessageSystemParticipantId ( const std::string &object_name, const NumericIdentifierType &id ) :
			name ( object_name ),
			id ( id )
		{
		}

	}
}
