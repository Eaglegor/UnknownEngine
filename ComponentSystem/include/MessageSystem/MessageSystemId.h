#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		class MessageSystemId
		{
			public:

				explicit MessageSystemId(const std::string &sender_name) :
					sender_name(sender_name)
				{
				}

				bool operator==(const MessageSystemId& rhs)
				{
					return sender_name == rhs.sender_name;
				}

				std::string toString(){
					return sender_name;
				}

			private:
				std::string sender_name;
		};
	}
}
