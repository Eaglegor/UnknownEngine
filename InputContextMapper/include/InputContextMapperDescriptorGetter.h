#pragma once

#include <CommonParsers/PropertiesParser.h>
#include <DescriptorContainer.h>
#include <InputContextMapperDescriptor.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace IO
	{
		class InputContextMapperDescriptorGetter : public boost::static_visitor<InputContextMapperDescriptor>
		{
			public:

				InputContextMapperDescriptor operator() ( const Core::DescriptorContainer& descriptor_container ) const
				{
					if ( descriptor_container.isEmpty() ) return InputContextMapperDescriptor();
					return descriptor_container.get<InputContextMapperDescriptor>();
				}

				InputContextMapperDescriptor operator() ( const Core::Properties& creation_options ) const
				{
					InputContextMapperDescriptor desc;

					using Utils::PropertiesParser;

					PropertiesParser::parse
					(
					    creation_options,
					{
						{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity> ( desc.log_level ) },
						{"action_slots_config_file", PropertiesParser::OptionalValue<std::string> ( desc.action_slots_config_file ) },
						{"input_layout_config_file", PropertiesParser::OptionalValue<std::string> ( desc.input_layout_config_file ) },
						{"update_frame_provider_name", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value){
							desc.update_frame_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						})}
					}
					);

					return desc;
				}
		};
	}
}
