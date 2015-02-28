#include <stdafx.h>

#include <ConsoleLogger.h>
#include <MessageSystem/PackedMessage.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Logger
	{

		using Core::LogSeverity;
		
		ConsoleLogger::ConsoleLogger( const std::string &name ) :
			name(name)
		{
		}

		void ConsoleLogger::processMessage ( const Core::PackedMessage &msg )
		{
			Utils::LogMessage unpacked_message = msg.get<Utils::LogMessage>();
			log ( unpacked_message.sender_info, unpacked_message.severity, unpacked_message.log_entry );
		}

		void ConsoleLogger::log ( const LogSeverity& severity, const std::string& msg )
		{
			log ( name, severity, msg );
		}

		void ConsoleLogger::log ( const std::string &sender, const LogSeverity &severity, const std::string &msg )
		{
			std::lock_guard<std::mutex> guard(lock);
			std::cout << "[";

			using Core::LogSeverity;
			
			switch ( severity )
			{
				case LogSeverity::INFO:
				{
					std::cout << "INFO";
					break;
				}
				case LogSeverity::ERROR_:
				{
					std::cout << "ERROR";
					break;
				}
				case LogSeverity::WARNING:
				{
					std::cout << "WARNING";
					break;
				}
				case LogSeverity::DEBUG:
				{
					std::cout << "DEBUG";
					break;
				}
				case LogSeverity::NONE:
				{
					// Doing nothing, only avoiding compiler warnings
					break;
				}
			}

			std::cout << "] ";

			std::cout << sender << ": ";
			std::cout << msg << std::endl;
		}

		const char* ConsoleLogger::getName() const
		{
			return name.c_str();
		}

	} // namespace Logger
} // namespace UnknownEngine
