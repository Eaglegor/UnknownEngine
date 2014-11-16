/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <ConsoleLoggerPlugin.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageSystem/MessageDictionary.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Logger
	{

		ConsoleLoggerPlugin::ConsoleLoggerPlugin ()
		{
		}

		ConsoleLoggerPlugin::~ConsoleLoggerPlugin ()
		{
		}

		bool ConsoleLoggerPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{

			console_logger.setDefaultSenderName(desc.name);
			
			console_logger.log(Utils::LogSeverity::INFO, "Installing console logger plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			console_logger.log(Utils::LogSeverity::INFO, "Console logger plugin installed");
			
			
			for(const Core::ReceivedMessageDesc &message : desc.received_messages )
			{
				console_logger.log(Utils::LogSeverity::INFO, "Registering listeners");
				
				if(message.message_type_name == Utils::LogMessage::getTypeName()){
				  
					console_logger.log(Utils::LogSeverity::INFO, "Registering log message listener");
					
					engine_context->getMessageDispatcher()->addListener(MESSAGE_TYPE_ID(Utils::LogMessage::getTypeName()), &console_logger);
				}
				else
				{
				  console_logger.log(Utils::LogSeverity::WARNING, "Found unsupported message type: " + message.message_type_name);
				}
			}
			
			
			return true;
		}

		bool ConsoleLoggerPlugin::init () 
		{
			console_logger.log(Utils::LogSeverity::INFO, "Initializing console logger plugin");

			console_logger.log(Utils::LogSeverity::INFO, "Console logger plugin initialized");
			
			return true;
		}

		bool ConsoleLoggerPlugin::shutdown () 
		{
			console_logger.log(Utils::LogSeverity::INFO, "Shutting down console logger plugin");
			
			console_logger.log(Utils::LogSeverity::INFO, "Unregistering log messages listener");
			
			engine_context->getMessageDispatcher()->removeListener(&console_logger);
			
			console_logger.log(Utils::LogSeverity::INFO, "Console logger plugin is shut down");
			
			return true;
		}

		bool ConsoleLoggerPlugin::uninstall () 
		{
			console_logger.log(Utils::LogSeverity::INFO, "Uninstalling console logger plugin");
			
			console_logger.log(Utils::LogSeverity::INFO, "Console logger plugin is uninstalled");
			
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
