#pragma once

/*
 * DirectX10RenderSystem.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <RenderSystem.h>
#include <RenderWindow.h>

#include <PluginExport.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static const String DX10_RENDER_SYSTEM_NAME("UnknownEngine_DX10_RenderSystem");

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
				HINSTANCE getHInstance(){return hInstance;}

			private:
				HINSTANCE hInstance;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
