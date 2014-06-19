/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <RenderSystem/DirectX11RenderSystem.h>
#include <Plugins/PluginsManager.h>
#include <DirectX11RenderSystemPlugin.h>
#include <MessageSystem/MessageDispatcher.h>

#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/RenderSystem/CreateRenderWindowMessage.h>

#include <RenderSystem/RenderSystemUpdateFrameListener.h>
#include <RenderSystem/RenderSystemCreateRenderWindowListener.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Graphics
	{

		static RenderSystem* render_system_instance;
		static RenderSystemUpdateFrameListener* listener_instance;
		static RenderSystemCreateRenderWindowListener* create_render_window_listener_instance;

		DirectX11RenderSystemPlugin::DirectX11RenderSystemPlugin ( HINSTANCE hInstance )
				: hInstance ( hInstance )
		{
		}

		DirectX11RenderSystemPlugin::~DirectX11RenderSystemPlugin ()
		{
			// TODO Auto-generated destructor stub
		}

		std::string DirectX11RenderSystemPlugin::getName () const
		{
			return "DirectX11RenderSystemPlugin";
		}

		bool DirectX11RenderSystemPlugin::install ( Core::PluginsManager* plugins_manager ) throw ( Core::PluginError )
		{
			Core::MessageDispatcher::initInstance(plugins_manager->getMessageDispatcher());
			Core::MessageDictionary::initInstance(plugins_manager->getMessageDictionary());
			Core::ComponentManager::initInstance(plugins_manager->getComponentManager());

			return true;
		}

		bool DirectX11RenderSystemPlugin::init () throw ( Core::PluginError )
		{
			render_system_instance = new DirectX11RenderSystem ( hInstance );
			listener_instance = new RenderSystemUpdateFrameListener ( render_system_instance );
			create_render_window_listener_instance = new RenderSystemCreateRenderWindowListener( render_system_instance );

			Core::MessageDispatcher::getSingleton()->addListener ( Core::UpdateFrameMessage::MSG_TYPE_NAME, listener_instance );
			Core::MessageDispatcher::getSingleton()->addListener ( Graphics::CreateRenderWindowMessage::MSG_TYPE_NAME, listener_instance );
		}

		bool DirectX11RenderSystemPlugin::shutdown () throw ( Core::PluginError )
		{
			return true;
		}

		bool DirectX11RenderSystemPlugin::uninstall () throw ( Core::PluginError )
		{
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
