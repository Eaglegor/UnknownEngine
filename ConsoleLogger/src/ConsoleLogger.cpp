#include <ConsoleLogger.h>
#include <MessageSystem/PackedMessage.h>

namespace UnknownEngine {
	namespace Logger {

		ConsoleLogger::ConsoleLogger():
			Core::IMessageListener( Core::MessageSystemId("ConsoleLogger.LoggerObject") )
		{
		}

		std::string ConsoleLogger::getName() const
		{
			return "ConsoleLoggerClass";
		}

		void ConsoleLogger::processMessage(const Core::PackedMessage &msg)
		{
			log(msg.getSenderInfo().toString(), message_unpacker.unpackMessage(msg).log_entry);
		}

		void ConsoleLogger::log(const std::string &sender, const std::string &msg)
		{
			std::cout << sender << ": ";
			std::cout << msg << std::endl;
		}


	} // namespace Logger
} // namespace UnknownEngine
