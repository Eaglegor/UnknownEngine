#pragma once

#include <string>

#include <MessageSystem/Message.h>
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Utils
	{

		/**
		 * @brief Log entry message
		 *
		 * Just a log message with specified severity.
		 * Purposed to be catched by logging subsystems.
		 * Recommended to be broadcasted to be catched by all logging subsystems.
		 */

		struct LogMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Utils.LogMessage";}
			
			std::string sender_info;
			std::string log_entry;
			LogSeverity severity;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
