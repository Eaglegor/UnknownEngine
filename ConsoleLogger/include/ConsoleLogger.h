#pragma once

#include <MessageSystem/IMessageListener.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine {
	namespace Logger {

		class ConsoleLogger : public Core::IMessageListener
		{
			public:
				void processMessage(const Core::PackedMessage &msg) override;
				void log(const std::string &sender, const Core::LogMessage::Severity &severity, const std::string &msg);
				void log(const Core::LogMessage::Severity &severity, const std::string &msg);
				ConsoleLogger();
				
				void setDefaultSenderName(const std::string &name);
				
			private:
				std::string name;
		};

	} // namespace Logger
} // namespace UnknownEngine

