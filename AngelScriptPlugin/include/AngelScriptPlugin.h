#pragma once

#include <InlineSpecification.h>
#include <Plugins/Plugin.h>
#include <SubsystemDesc.h>
#include <memory>

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

	namespace Behavior
	{

		class AngelScriptPlugin: public Core::Plugin
		{
			public:
				AngelScriptPlugin();
				virtual ~AngelScriptPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				std::unique_ptr<Utils::LogHelper> log_helper;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
