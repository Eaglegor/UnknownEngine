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
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Dummy
	{

		DummySubsystemPlugin::DummySubsystemPlugin ()
		:log_helper(nullptr)
		{
		}

		DummySubsystemPlugin::~DummySubsystemPlugin ()
		{
		}

		bool DummySubsystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) throw ( Core::PluginError )
		{
		  
			log_helper = new Core::LogHelper(getName(), Core::LogMessage::Severity::LOG_SEVERITY_INFO, plugins_manager->getEngineContext());
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing dummy plugin");

			// Saving context for later use
			// Right now we don't know if all needed subsystems are already installed
			// That's why we do all init stuff in init() method
			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			// Exporting interface messages of out subsystem
			LOG_INFO(log_helper, "Registering dummy message type stub")
			engine_context->getMessageDictionary()->registerNewMessageType("DummySubsystem.Test.TestMessageType");

			return true;
		}

		bool DummySubsystemPlugin::init () throw ( Core::PluginError )
		{
			LOG_INFO(log_helper, "Initializing dummy plugin")

			return true;
		}

		bool DummySubsystemPlugin::shutdown () throw ( Core::PluginError )
		{
			LOG_INFO(log_helper, "Shutting down dummy plugin");
		  
			return true;
		}

		bool DummySubsystemPlugin::uninstall () throw ( Core::PluginError )
		{
			LOG_INFO(log_helper, "Uninstalling dummy plugin");
		  
			if(log_helper) delete log_helper;
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
