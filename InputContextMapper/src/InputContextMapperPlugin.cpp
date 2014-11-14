#include <stdafx.h>
#include <InputContextMapper.h>
#include <InputContextMapperPlugin.h>
#include <InputContextMapperDescriptorGetter.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <ExportedMessages/InputContext/AddRangeActionMessage.h>
#include <LogHelper.h>

namespace UnknownEngine
{
    namespace IO
    {

		InputContextMapperPlugin::InputContextMapperPlugin(){}
		InputContextMapperPlugin::~InputContextMapperPlugin(){}


        bool InputContextMapperPlugin::install(Core::PluginsManager *plugins_manager, Core::SubsystemDesc const &desc) {
            this->desc = desc;
            this->engine_context = plugins_manager->getEngineContext();
			
			this->engine_context->getMessageDictionary()->registerNewMessageType(AddSimpleActionMessage::getTypeName());
			this->engine_context->getMessageDictionary()->registerNewMessageType(AddRangeActionMessage::getTypeName());
			
            return true;
        }

        bool InputContextMapperPlugin::init() {

            InputContextMapperDescriptorGetter descriptor_getter;
            InputContextMapperDescriptor mapper_descriptor = desc.descriptor.apply_visitor(descriptor_getter);

			if (mapper_descriptor.log_level > Utils::LogSeverity::NONE)
			{
				log_helper.reset(new Utils::LogHelper(std::string(getName()), mapper_descriptor.log_level, engine_context));
			}

            InputContextMapperCreationOptions creation_options;
            creation_options.log_helper = log_helper.get();
            creation_options.engine_context = engine_context;
            creation_options.received_messages = desc.received_messages;
            creation_options.name = std::string(getName());

            context_mapper.reset( new InputContextMapper(mapper_descriptor, creation_options, log_helper.get()) );

            return true;
        }

        bool InputContextMapperPlugin::shutdown() {
            context_mapper.reset();
            log_helper.reset();
            return true;
        }

        bool InputContextMapperPlugin::uninstall() {
            return true;
        }

    }
}