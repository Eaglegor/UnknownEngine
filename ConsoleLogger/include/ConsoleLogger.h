#pragma once

#include <MessageSystem/IMessageListener.h>
#include <LogSeverity.h>
#include <mutex>

namespace UnknownEngine {
	
	namespace Utils
	{
		struct LogMessage;
	}
	
	namespace Logger {

		class ConsoleLogger : public Core::IMessageListener
		{
			public:
				virtual const char* getName() const;
				void processMessage(const Core::PackedMessage &msg) override;
				void log(const std::string &sender, const Core::LogSeverity &severity, const std::string &msg);
				void log(const Core::LogSeverity &severity, const std::string &msg);
				ConsoleLogger(const std::string &name);
				
			private:
				std::mutex lock;
				std::string name;
		};

	} // namespace Logger
} // namespace UnknownEngine

