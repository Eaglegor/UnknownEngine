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
		struct SubsystemDesc;
		class EngineContext;
	}
	
	namespace Utils
	{
		class LogHelper;
	}

	namespace Dummy
	{

		class DummySubsystemPlugin: public Core::Plugin
		{
			public:
				DummySubsystemPlugin();
				virtual ~DummySubsystemPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				Utils::LogHelper* log_helper;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
