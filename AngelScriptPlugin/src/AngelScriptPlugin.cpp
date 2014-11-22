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
#include <Descriptors/AngelScriptSubsystemDesc.h>
#include <AngelScriptSubsystem.h>
#include <MessageSystem/MessageDictionary.h>
#include <EngineContext.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		AngelScriptPlugin::AngelScriptPlugin ()
		{
		}

		AngelScriptPlugin::~AngelScriptPlugin ()
		{
		}

		bool AngelScriptPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
			this->desc = desc;

			engine_context = plugins_manager->getEngineContext();
			
			AngelScriptSubsystemDesc asdesc;
			angel_script_subsystem.reset(new AngelScriptSubsystem(getName(), asdesc, engine_context));

			return true;
		}

		bool AngelScriptPlugin::init () 
		{
			angel_script_subsystem->init();
		
			return true;
		}

		bool AngelScriptPlugin::shutdown () 
		{
			angel_script_subsystem->shutdown();
			
			return true;
		}

		bool AngelScriptPlugin::uninstall () 
		{
			angel_script_subsystem.reset();
			log_helper.reset();
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
