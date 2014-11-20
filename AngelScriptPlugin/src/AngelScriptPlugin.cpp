/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <AngelScriptPlugin.h>
#include <MessageSystem/MessageDictionary.h>
#include <EngineContext.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		AngelScriptPlugin::AngelScriptPlugin ()
		:log_helper(nullptr)
		{
		}

		AngelScriptPlugin::~AngelScriptPlugin ()
		{
		}

		bool AngelScriptPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			log_helper = new Utils::LogHelper(getName(), Utils::LogSeverity::INFO, plugins_manager->getEngineContext());
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing dummy plugin");

			this->desc = desc;
			
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool AngelScriptPlugin::init () 
		{
			LOG_INFO(log_helper, "Initializing dummy plugin")

			return true;
		}

		bool AngelScriptPlugin::shutdown () 
		{
			LOG_INFO(log_helper, "Shutting down dummy plugin");
		  
			return true;
		}

		bool AngelScriptPlugin::uninstall () 
		{
			LOG_INFO(log_helper, "Uninstalling dummy plugin");
		  
			if(log_helper) delete log_helper;
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
