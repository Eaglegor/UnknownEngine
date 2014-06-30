#pragma once

#include <MessageSystem/IMessageListener.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine {
	namespace Logger {

		class ConsoleLogger : public Core::IMessageListener
		{
			public:
				void processMessage(const Core::PackedMessage &msg) override;
				void log(const std::string &sender, const std::string &msg);
				ConsoleLogger();
			private:
				Core::LogMessageUnpacker message_unpacker;
		};

	} // namespace Logger
} // namespace UnknownEngine

