#pragma once

#include <Plugins/BasePlugin.h>
#include <Plugins/PluginsManager.h>
#include <Plugins/SubsystemDesc.h>
#include <memory>

namespace UnknownEngine
{

    namespace Core
    {
        class EngineContext;
		class ILogger;
    }

    namespace IO
    {
        class InputContextMapper;

        class InputContextMapperPlugin : public Core::BasePlugin
        {
        public:
			InputContextMapperPlugin(const char* name);
			virtual ~InputContextMapperPlugin();


            virtual bool install(Core::PluginsManager *plugins_manager, Core::SubsystemDesc const &desc) override;

            virtual bool init() override;

            virtual bool shutdown() override;

            virtual bool uninstall() override;

        private:
            Core::SubsystemDesc desc;
            Core::ILogger* logger;
            std::unique_ptr<InputContextMapper> context_mapper;
            Core::EngineContext* engine_context;

        };
    }
}