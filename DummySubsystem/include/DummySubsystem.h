#pragma once

#include <InlineSpecification.h>
#include <Plugins/Plugin.h>
#include <SubsystemDesc.h>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
		class ILogger;
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
				Core::ILogger* logger;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
