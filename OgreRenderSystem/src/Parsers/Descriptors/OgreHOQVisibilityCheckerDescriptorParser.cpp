#include <stdafx.h>

#include <CommonParsers/PropertiesParser.h>
#include <Parsers/Descriptors/OgreHOQVisibilityCheckerDescriptorParser.h>
#include <ComponentSystem/ComponentsManager.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreHOQVisibilityCheckerDesc OgreHOQVisibilityCheckerDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreHOQVisibilityCheckerDesc desc;
			
			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				properties,
				{
					{"checkable_object", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value){
						desc.checkable_object = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
					})},
					{"render_window", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value){
						desc.render_window = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
					})},
					{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity>(desc.log_level)},
					{"render_queue_group", PropertiesParser::OptionalValue<uint8_t>(desc.render_queue_group) }
				}
			);
			
			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
