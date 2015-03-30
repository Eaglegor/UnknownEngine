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
#include <Factories/AngelScriptComponentFactory.h>
#include <MessageSystem/MessageDictionary.h>
#include <ComponentSystem/ComponentsManager.h>
#include <EngineContext.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		AngelScriptPlugin::AngelScriptPlugin (const char* name):
		Core::BasePlugin(name)
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
		
			angel_script_component_factory.reset(new AngelScriptComponentFactory(angel_script_subsystem.get()));
			engine_context->getComponentsManager()->addComponentFactory(angel_script_component_factory.get());
			
			return true;
		}

		bool AngelScriptPlugin::shutdown () 
		{
			engine_context->getComponentsManager()->removeComponentFactory(angel_script_component_factory.get());
			angel_script_component_factory.reset();
			
			angel_script_subsystem->shutdown();
			
			return true;
		}

		bool AngelScriptPlugin::uninstall () 
		{
			angel_script_subsystem.reset();
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
