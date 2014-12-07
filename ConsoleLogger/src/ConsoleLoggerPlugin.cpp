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
#include <MessageSystem/MessageDictionary.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Logger
	{

		ConsoleLoggerPlugin::ConsoleLoggerPlugin (const char* name):
		Core::BasePlugin(name)
		{
		}

		ConsoleLoggerPlugin::~ConsoleLoggerPlugin ()
		{
		}

		bool ConsoleLoggerPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{

			console_logger.reset(new ConsoleLogger(desc.name));
			
			console_logger->log(Core::LogSeverity::INFO, "Installing console logger plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			console_logger->log(Core::LogSeverity::INFO, "Console logger plugin installed");
			
			console_logger->log(Core::LogSeverity::INFO, "Registering log message listener");
			
			engine_context->getMessageDispatcher()->addListener(MESSAGE_TYPE_ID(Utils::LogMessage::getTypeName()), console_logger.get());

			return true;
		}

		bool ConsoleLoggerPlugin::init () 
		{
			console_logger->log(Core::LogSeverity::INFO, "Initializing console logger plugin");

			console_logger->log(Core::LogSeverity::INFO, "Console logger plugin initialized");
			
			return true;
		}

		bool ConsoleLoggerPlugin::shutdown () 
		{
			console_logger->log(Core::LogSeverity::INFO, "Shutting down console logger plugin");
			
			console_logger->log(Core::LogSeverity::INFO, "Unregistering log messages listener");
			
			engine_context->getMessageDispatcher()->removeListener(console_logger.get());
			
			console_logger->log(Core::LogSeverity::INFO, "Console logger plugin is shut down");
			
			return true;
		}

		bool ConsoleLoggerPlugin::uninstall () 
		{
			console_logger->log(Core::LogSeverity::INFO, "Uninstalling console logger plugin");
			
			console_logger->log(Core::LogSeverity::INFO, "Console logger plugin is uninstalled");
			
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
