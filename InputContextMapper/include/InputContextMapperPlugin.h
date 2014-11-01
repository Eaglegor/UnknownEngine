#pragma once

#include <Plugins/Plugin.h>
#include <Plugins/PluginsManager.h>
#include <SubsystemDesc.h>
#include <memory>

namespace UnknownEngine
{

    namespace Core
    {
        class EngineContext;
    }
    
    namespace Utils
    {
		class LogHelper;
    }

    namespace IO
    {
        class InputContextMapper;

        class InputContextMapperPlugin : public Core::Plugin
        {
        public:
			InputContextMapperPlugin();
			virtual ~InputContextMapperPlugin();


            virtual bool install(Core::PluginsManager *plugins_manager, Core::SubsystemDesc const &desc);

            virtual bool init();

            virtual bool shutdown();

            virtual bool uninstall();

        private:
            Core::SubsystemDesc desc;
            std::unique_ptr<Utils::LogHelper> log_helper;
            std::unique_ptr<InputContextMapper> context_mapper;
            Core::EngineContext* engine_context;

        };
    }
}