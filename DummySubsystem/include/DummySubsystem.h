#pragma once

/*
 * DirectX10RenderSystemPlugin.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <InlineSpecification.h>
#include <Plugins/Plugin.h>
#include <SubsystemDesc.h>

namespace UnknownEngine
{

	namespace Core
	{
		class SubsystemDesc;
		class EngineContext;
		class LogHelper;
	}

	namespace Dummy
	{

		class DummySubsystemPlugin: public Core::Plugin
		{
			public:
				DummySubsystemPlugin();
				virtual ~DummySubsystemPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc) throw (Core::PluginError) override;
				virtual bool init() throw (Core::PluginError) override;
				virtual bool shutdown() throw (Core::PluginError) override;
				virtual bool uninstall() throw (Core::PluginError) override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				Core::LogHelper* log_helper;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
