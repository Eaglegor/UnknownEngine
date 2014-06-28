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

			console_logger.log("ConsoleLogger", "Installing console logger plugin");

			this->desc = desc;
			message_dictionary = plugins_manager->getMessageDictionary();
			message_dispatcher = plugins_manager->getMessageDispatcher();
			components_manager = plugins_manager->getComponentsManager();

			return true;
		}

		bool ConsoleLoggerPlugin::init () throw ( Core::PluginError )
		{
			console_logger.log("ConsoleLogger", "Initializing console logger plugin");

			for(Core::MessageListenerDesc &listener : desc.message_listeners)
			{
				for(Core::MessageListenerDesc::MessageDesc &message : listener.messages )
				{
					console_logger.log("ConsoleLogger", "Registering new log listener");
					if(message.message_type_name == Core::LogMessage::getTypeName()){
						message_dispatcher->addListener(Core::LogMessage::getTypeName(), &console_logger);
					}
				}
			}

			return true;
		}

		bool ConsoleLoggerPlugin::shutdown () throw ( Core::PluginError )
		{
			console_logger.log("ConsoleLogger", "Shutting down console logger plugin");
			return true;
		}

		bool ConsoleLoggerPlugin::uninstall () throw ( Core::PluginError )
		{
			console_logger.log("ConsoleLogger", "Uninstalling console logger plugin");
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
