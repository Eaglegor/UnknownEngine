#pragma once

/*
 * DirectX10RenderSystem.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <RenderSystem/RenderSystem.h>
#include <RenderTargets/RenderWindow.h>

#include <Plugins/PluginExport.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static const String DX10_RENDER_SYSTEM_NAME("RenderSystem.D3D10");

		class DirectX10RenderSystem: public RenderSystem
		{
			public:
				DirectX10RenderSystem (HINSTANCE hInstance);
				virtual ~DirectX10RenderSystem ();

				UNKNOWNENGINE_PLUGIN_INTERFACE
				RenderWindow* createRenderWindow(const RenderWindowDesc &windowDesc) override;

				UNKNOWNENGINE_PLUGIN_INTERFACE
				UNKNOWNENGINE_INLINE
				String getName() const {return DX10_RENDER_SYSTEM_NAME;}

				UNKNOWNENGINE_INLINE
				HINSTANCE getHInstance() const {return hInstance;}

			private:
				HINSTANCE hInstance;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
