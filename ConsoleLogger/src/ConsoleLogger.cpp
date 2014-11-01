#include <stdafx.h>

#include <ConsoleLogger.h>
#include <MessageSystem/PackedMessage.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Logger
	{

		using Utils::LogSeverity;
		
		ConsoleLogger::ConsoleLogger( ) :
			Core::IMessageListener ( "Logger.ConsoleLogger.LoggerObject" )
		{
		}

		void ConsoleLogger::processMessage ( const Core::PackedMessage &msg )
		{
			Utils::LogMessage unpacked_message = msg.get<Utils::LogMessage>();
			log ( msg.getSenderInfo().name, unpacked_message.severity, unpacked_message.log_entry );
		}

		void ConsoleLogger::log ( const LogSeverity& severity, const std::string& msg )
		{
			log ( name, severity, msg );
		}

		void ConsoleLogger::log ( const std::string &sender, const LogSeverity &severity, const std::string &msg )
		{
			std::cout << "[";

			using Utils::LogSeverity;
			
			switch ( severity )
			{
			case LogSeverity::INFO:
				std::cout << "INFO";
				break;
			case LogSeverity::ERROR:
				std::cout << "ERROR";
				break;
			case LogSeverity::WARNING:
				std::cout << "WARNING";
				break;
			case LogSeverity::DEBUG:
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
