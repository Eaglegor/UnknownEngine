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
		class LogHelper;
		class BaseMessageListener;
		struct UpdateFrameMessage;
	}

	namespace Behavior
	{

		class SimpleBehaviorsPerformer;

		class SimpleBehaviorsFactory;

		class SimpleBehaviorPlugin: public Core::Plugin
		{
			public:
				SimpleBehaviorPlugin();
				virtual ~SimpleBehaviorPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc) throw (Core::PluginError) override;
				virtual bool init() throw (Core::PluginError) override;
				virtual bool shutdown() throw (Core::PluginError) override;
				virtual bool uninstall() throw (Core::PluginError) override;
				
				void onUpdateFrame(const Core::UpdateFrameMessage& msg);

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				std::unique_ptr<Core::LogHelper> log_helper;

				std::unique_ptr<SimpleBehaviorsPerformer> behaviors_performer;
				std::unique_ptr<Core::BaseMessageListener> listener;
				std::unique_ptr<SimpleBehaviorsFactory> simple_behaviors_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
