#pragma once

/*
 * DirectX10RenderSystemPlugin.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <Plugins/PluginExport.h>
#include <Plugins/Plugin.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX11RenderSystemPlugin: public Core::Plugin
		{
			public:
				DirectX11RenderSystemPlugin(HINSTANCE hInstance);
				virtual ~DirectX11RenderSystemPlugin();

				constexpr static const char* getNameConst()
				{
					return "DirectX11RenderSystemPlugin";
				}

				UNKNOWNENGINE_INLINE
				virtual const char* getName() const override
				{
					return getNameConst();
				}

				virtual bool install(Core::PluginsManager* plugins_manager) throw (Core::PluginError) override;

				virtual bool init() throw (Core::PluginError) override;

				virtual bool shutdown() throw (Core::PluginError) override;

				virtual bool uninstall() throw (Core::PluginError) override;

			private:
				HINSTANCE hInstance;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
