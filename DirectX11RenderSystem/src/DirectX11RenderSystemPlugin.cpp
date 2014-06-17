/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 ���� 2014 �.
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

		DirectX11RenderSystemPlugin::DirectX11RenderSystemPlugin ()
		{
			// TODO Auto-generated constructor stub

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

			TCHAR* module_name = new TCHAR[512];
			GetModuleFileNameA(NULL, module_name, 512);

			std::cout << module_name << std::endl;

			HINSTANCE hInstance = GetModuleHandle(module_name);

			RenderSystem* render_system = new DirectX11RenderSystem(hInstance);
			plugins_manager->addRenderSystem(render_system);

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