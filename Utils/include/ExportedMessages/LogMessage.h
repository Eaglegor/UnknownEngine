#pragma once

#include <string>

#include <MessageSystem/Message.h>
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Utils
	{
		struct LogMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Utils.LogMessage";}
			
			std::string sender_info;
			std::string log_entry;
			Core::LogSeverity severity;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
