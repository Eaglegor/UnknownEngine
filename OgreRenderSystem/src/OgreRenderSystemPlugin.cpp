/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <OgreRenderSystemPlugin.h>
#include <MessageSystem/MessageDispatcher.h>

#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/RenderSystem/ChangeMaterialActionMessage.h>
#include <Properties/Properties.h>
#include <EngineContext.h>
#include <OgreRenderSystem.h>

#include <ComponentsManager.h>
#include <Factories/OgreRenderableComponentsFactory.h>


namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderSystemPlugin::OgreRenderSystemPlugin ()
		{
		}

		OgreRenderSystemPlugin::~OgreRenderSystemPlugin ()
		{
			// TODO Auto-generated destructor stub
		}

		bool OgreRenderSystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc &desc ) throw ( Core::PluginError )
		{
			this->desc = desc;
			this->engine_context = plugins_manager->getEngineContext();

			engine_context->getMessageDictionary()->registerNewMessageType(ChangeMaterialActionMessage::getTypeName());

			render_system = new OgreRenderSystem();
			renderable_components_factory = new OgreRenderableComponentsFactory(render_system);

			engine_context->getComponentsManager()->addComponentFactory(renderable_components_factory);

			return true;
		}

		bool OgreRenderSystemPlugin::init () throw ( Core::PluginError )
		{

			return true;
		}

		bool OgreRenderSystemPlugin::shutdown () throw ( Core::PluginError )
		{
			return true;
		}

		bool OgreRenderSystemPlugin::uninstall () throw ( Core::PluginError )
		{
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
