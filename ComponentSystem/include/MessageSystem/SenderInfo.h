#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		struct SenderInfo
		{
				explicit SenderInfo(std::string sender_name) :
						sender_name(sender_name)
				{

				}

				bool operator==(const SenderInfo& rhs)
				{
					return sender_name == rhs.sender_name;
				}

				std::string sender_name;
		};
	}
}
