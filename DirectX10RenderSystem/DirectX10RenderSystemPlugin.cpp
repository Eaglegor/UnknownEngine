/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <DirectX10RenderSystem.h>
#include <PluginsManager.h>
#include <DirectX10RenderSystemPlugin.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		DirectX10RenderSystemPlugin::DirectX10RenderSystemPlugin ()
		{
			// TODO Auto-generated constructor stub

		}

		DirectX10RenderSystemPlugin::~DirectX10RenderSystemPlugin ()
		{
			// TODO Auto-generated destructor stub
		}

		std::string DirectX10RenderSystemPlugin::getName () const
		{
			return "DirectX10RenderSystemPlugin";
		}

		bool DirectX10RenderSystemPlugin::install ( Core::PluginsManager* plugins_manager ) throw ( Core::PluginError )
		{

			HINSTANCE hInstance = GetModuleHandle("libDirectX10RenderSystem.dll");

			RenderSystem* render_system = new DirectX10RenderSystem(hInstance);
			plugins_manager->addRenderSystem(render_system);

			return true;

		}

		bool DirectX10RenderSystemPlugin::init () throw ( Core::PluginError )
		{
		}

		bool DirectX10RenderSystemPlugin::shutdown () throw ( Core::PluginError )
		{
		}

		bool DirectX10RenderSystemPlugin::uninstall () throw ( Core::PluginError )
		{
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
