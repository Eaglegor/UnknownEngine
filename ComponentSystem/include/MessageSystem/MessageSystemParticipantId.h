#pragma once

#include <string>
#include <NumericIdentifierType.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct MessageSystemParticipantId
		{
			explicit MessageSystemParticipantId(const std::string &sender_name);
			MessageSystemParticipantId(const std::string &sender_name, const NumericIdentifierType &id);

			bool operator==(const MessageSystemParticipantId& rhs) const
			{
				if(id != INVALID_NUMERIC_IDENTIFIER && rhs.id != INVALID_NUMERIC_IDENTIFIER)
				{
					return id == rhs.id;
				}
				return name == rhs.name;
			}

			NumericIdentifierType id;
			std::string name;
		};
	}
}
