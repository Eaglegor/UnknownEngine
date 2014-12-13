#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <LogHelper.h>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
	}

	namespace Endoscopy
	{

		class ESInstrumentAlgorithmsPlugin: public Core::BasePlugin
		{
			public:
				ESInstrumentAlgorithmsPlugin(const char* name);
				virtual ~ESInstrumentAlgorithmsPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				Core::LogHelper logger;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
