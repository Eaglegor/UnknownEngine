#include <stdafx.h>

#include <ConsoleLogger.h>
#include <MessageSystem/PackedMessage.h>

namespace UnknownEngine
{
	namespace Logger
	{

		ConsoleLogger::ConsoleLogger( ) :
			Core::IMessageListener ( "Logger.ConsoleLogger.LoggerObject" )
		{
		}

		void ConsoleLogger::processMessage ( const Core::PackedMessage &msg )
		{
			Core::LogMessage unpacked_message = msg.get<Core::LogMessage>();
			log ( msg.getSenderInfo().name, unpacked_message.severity, unpacked_message.log_entry );
		}

		void ConsoleLogger::log ( const Core::LogMessage::Severity& severity, const std::string& msg )
		{
			log ( name, severity, msg );
		}


		void ConsoleLogger::log ( const std::string &sender, const Core::LogMessage::Severity &severity, const std::string &msg )
		{
			std::cout << "[";

			switch ( severity )
			{
			case Core::LogMessage::Severity::LOG_SEVERITY_INFO:
				std::cout << "INFO";
				break;
			case Core::LogMessage::Severity::LOG_SEVERITY_ERROR:
				std::cout << "ERROR";
				break;
			case Core::LogMessage::Severity::LOG_SEVERITY_WARNING:
				std::cout << "WARNING";
				break;
			case Core::LogMessage::Severity::LOG_SEVERITY_DEBUG:
				std::cout << "DEBUG";
				break;
			}

			std::cout << "] ";

			std::cout << sender << ": ";
			std::cout << msg << std::endl;
		}

		void ConsoleLogger::setDefaultSenderName ( const std::string& name )
		{
			this->name = name;
		}


	} // namespace Logger
} // namespace UnknownEngine
