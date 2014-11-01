#pragma once

#include <MessageSystem/IMessageListener.h>
#include <LogSeverity.h>

namespace UnknownEngine {
	
	namespace Utils
	{
		struct LogMessage;
	}
	
	namespace Logger {

		class ConsoleLogger : public Core::IMessageListener
		{
			public:
				void processMessage(const Core::PackedMessage &msg) override;
				void log(const std::string &sender, const Utils::LogSeverity &severity, const std::string &msg);
				void log(const Utils::LogSeverity &severity, const std::string &msg);
				ConsoleLogger();
				
				void setDefaultSenderName(const std::string &name);
				
			private:
				std::string name;
		};

	} // namespace Logger
} // namespace UnknownEngine

