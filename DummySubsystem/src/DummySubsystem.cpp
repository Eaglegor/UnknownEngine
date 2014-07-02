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

#define LOG(s) std::cout << s << std::endl

namespace UnknownEngine
{
	namespace Dummy
	{

		DummySubsystemPlugin::DummySubsystemPlugin ()
		{
			LOG("Instantiating dummy plugin object");
		}

		DummySubsystemPlugin::~DummySubsystemPlugin ()
		{
			LOG("Destroying dummy plugin instance");
		}

		bool DummySubsystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) throw ( Core::PluginError )
		{

			LOG("Installing dummy plugin");

			// Saving context for later use
			// Right now we don't know if all needed subsystems are already installed
			// That's why we do all init stuff in init() method
			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			// Exporting interface messages of out subsystem
			engine_context->getMessageDictionary()->registerNewMessageType("DummySubsystem.Test.TestMessageType");

			return true;
		}

		bool DummySubsystemPlugin::init () throw ( Core::PluginError )
		{

			LOG("Initializing dummy plugin");

			return true;
		}

		bool DummySubsystemPlugin::shutdown () throw ( Core::PluginError )
		{
			LOG("Shutting down dummy plugin");
			return true;
		}

		bool DummySubsystemPlugin::uninstall () throw ( Core::PluginError )
		{
			LOG("Uninstalling dummy plugin");
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
