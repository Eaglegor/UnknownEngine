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

		bool ConsoleLoggerPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) throw ( Core::PluginError )
		{

			setName(desc.name);
		  
			console_logger.setDefaultSenderName(desc.name);
			
			console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Installing console logger plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Console logger plugin installed");
			
			
			for(const Core::ReceivedMessageDesc &message : desc.received_messages )
			{
				console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Registering listeners");
				
				if(message.message_type_name == Core::LogMessage::getTypeName()){
				  
					console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Registering log message listener");
					
					engine_context->getMessageDispatcher()->addListener(Core::LogMessage::getTypeName(), &console_logger);
				}
				else
				{
				  console_logger.log(Core::LogMessage::LOG_SEVERITY_WARNING, "Found unsupported message type: " + message.message_type_name);
				}
			}
			
			
			return true;
		}

		bool ConsoleLoggerPlugin::init () throw ( Core::PluginError )
		{
			console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Initializing console logger plugin");

			console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Console logger plugin initialized");
			
			return true;
		}

		bool ConsoleLoggerPlugin::shutdown () throw ( Core::PluginError )
		{
			console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Shutting down console logger plugin");
			
			console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Console logger plugin is shut down");
			
			return true;
		}

		bool ConsoleLoggerPlugin::uninstall () throw ( Core::PluginError )
		{
			console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Uninstalling console logger plugin");
			
			console_logger.log(Core::LogMessage::LOG_SEVERITY_INFO, "Console logger plugin is uninstalled");
			
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
