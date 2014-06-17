/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <RenderSystem/DirectX11RenderSystem.h>
#include <Plugins/PluginsManager.h>
#include <DirectX11RenderSystemPlugin.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Graphics
	{

		DirectX11RenderSystemPlugin::DirectX11RenderSystemPlugin ( HINSTANCE hInstance )
				: hInstance( hInstance )
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

			RenderSystem* render_system = new DirectX11RenderSystem( hInstance );
			plugins_manager->addRenderSystem( render_system );

			return true;

		}

		bool DirectX11RenderSystemPlugin::init () throw ( Core::PluginError )
		{
			return true;
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
