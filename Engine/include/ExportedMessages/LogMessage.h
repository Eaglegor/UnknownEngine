#pragma once

#include <string>

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Log entry message
		 *
		 * Just a log message with specified severity.
		 * Purposed to be catched by logging subsystems.
		 * Recommended to be broadcasted to be catched by all logging subsystems.
		 */

		struct LogMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.LogMessage";}
			
			enum class Severity : int
			{
			    LOG_SEVERITY_NONE = 0,
			    LOG_SEVERITY_ERROR = 1,
			    LOG_SEVERITY_WARNING = 2,
			    LOG_SEVERITY_INFO = 3,
			    LOG_SEVERITY_DEBUG = 4
			};

			std::string log_entry;
			Severity severity;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
