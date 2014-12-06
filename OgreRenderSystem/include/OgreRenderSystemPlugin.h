#pragma once

/*
 * OgreRenderSystemPlugin.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <Plugins/Plugin.h>
#include <InlineSpecification.h>
#include <SubsystemDesc.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Graphics
	{

		class OgreRenderableComponentsFactory;
		class OgreCameraComponentsFactory;
		class OgreLightComponentsFactory;
		class OgreMeshPtrDataProvidersFactory;
		class OgreRenderSubsystem;
		
		class OgreRenderSystemPlugin: public Core::Plugin
		{
			public:
				OgreRenderSystemPlugin();
				virtual ~OgreRenderSystemPlugin();

				virtual bool install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc &desc )  override;

				virtual bool init()  override;

				virtual bool shutdown()  override;

				virtual bool uninstall()  override;

			private:

				Core::SubsystemDesc desc;
				Core::EngineContext *engine_context;

				std::unique_ptr<OgreRenderSubsystem> render_system;
				
				std::unique_ptr<OgreRenderableComponentsFactory> renderable_components_factory;
				std::unique_ptr<OgreCameraComponentsFactory> camera_components_factory;
				std::unique_ptr<OgreLightComponentsFactory> light_components_factory;
				
				std::unique_ptr<OgreMeshPtrDataProvidersFactory> mesh_ptr_data_providers_factory;

				Core::ILogger* logger;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
