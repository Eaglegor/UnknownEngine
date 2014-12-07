#include <stdafx.h>
#include <InputContextMapper.h>
#include <InputContextMapperPlugin.h>
#include <InputContextMapperDescriptorGetter.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <ExportedMessages/InputContext/AddRangeActionMessage.h>
#include <Logging.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
    namespace IO
    {

		InputContextMapperPlugin::InputContextMapperPlugin(const char* name):
		Core::BasePlugin(name)
		{}
		
		InputContextMapperPlugin::~InputContextMapperPlugin(){}


        bool InputContextMapperPlugin::install(Core::PluginsManager *plugins_manager, Core::SubsystemDesc const &desc) {
            this->desc = desc;
            this->engine_context = plugins_manager->getEngineContext();
			
            return true;
        }

        bool InputContextMapperPlugin::init() {

            InputContextMapperDescriptorGetter descriptor_getter;
            InputContextMapperDescriptor mapper_descriptor = desc.descriptor.apply_visitor(descriptor_getter);

			logger = CREATE_LOGGER(getName(), mapper_descriptor.log_level);

            InputContextMapperCreationOptions creation_options;
            creation_options.logger = logger;
            creation_options.engine_context = engine_context;
            creation_options.name = std::string(getName());

            context_mapper.reset( new InputContextMapper(mapper_descriptor, creation_options, logger) );

            return true;
        }

        bool InputContextMapperPlugin::shutdown() {
            context_mapper.reset();
            RELEASE_LOGGER(logger);
            return true;
        }

        bool InputContextMapperPlugin::uninstall() {
            return true;
        }

    }
}