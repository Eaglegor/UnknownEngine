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
#include <OgreRenderSubsystem.h>

#include <ComponentsManager.h>
#include <Factories/OgreRenderableComponentsFactory.h>
#include <Listeners/OgreUpdateFrameListener.h>


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

			render_system = new OgreRenderSubsystem(desc.prepared_descriptor.get<OgreRenderSubsystem::Descriptor>());
			renderable_components_factory = new OgreRenderableComponentsFactory(render_system);

			engine_context->getComponentsManager()->addComponentFactory(renderable_components_factory);

			return true;
		}

		bool OgreRenderSystemPlugin::init () throw ( Core::PluginError )
		{
			update_frame_listener = new OgreUpdateFrameListener("Graphics.Ogre.Listeners.UpdateFrameListener", render_system);
			engine_context->getMessageDispatcher()->addListener(Core::UpdateFrameMessage::getTypeName(), update_frame_listener);

			return true;
		}

		bool OgreRenderSystemPlugin::shutdown () throw ( Core::PluginError )
		{
			engine_context->getMessageDispatcher()->removeListener(update_frame_listener);
			delete update_frame_listener;

			return true;
		}

		bool OgreRenderSystemPlugin::uninstall () throw ( Core::PluginError )
		{

			engine_context->getComponentsManager()->removeComponentFactory(renderable_components_factory);
			delete renderable_components_factory;
			delete render_system;

			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
