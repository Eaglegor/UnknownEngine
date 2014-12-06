/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <DummySubsystem.h>
#include <MessageSystem/MessageDictionary.h>
#include <EngineContext.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Dummy
	{

		DummySubsystemPlugin::DummySubsystemPlugin ()
		:logger(nullptr)
		{
		}

		DummySubsystemPlugin::~DummySubsystemPlugin ()
		{
		}

		bool DummySubsystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			logger = CREATE_LOGGER(getName(), Core::LogSeverity::INFO);
		  
			LOG_INFO(logger, "Logger initialized");
			
			LOG_INFO(logger, "Installing dummy plugin");

			// Saving context for later use
			// Right now we don't know if all needed subsystems are already installed
			// That's why we do all init stuff in init() method
			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			// Exporting interface messages of out subsystem
			LOG_INFO(logger, "Registering dummy message type stub");
			engine_context->getMessageDictionary()->registerNewMessageType("DummySubsystem.Test.TestMessageType");

			return true;
		}

		bool DummySubsystemPlugin::init () 
		{
			LOG_INFO(logger, "Initializing dummy plugin");

			return true;
		}

		bool DummySubsystemPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down dummy plugin");
		  
			return true;
		}

		bool DummySubsystemPlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling dummy plugin");
		  
			RELEASE_LOGGER(logger);
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
