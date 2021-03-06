#include <stdafx.h>

#include <Parsers/Descriptors/OgrePointLightDescriptorParser.h>
#include <Parsers/Sections/OgreLightSettingsParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <CommonParsers/PropertiesParser.h>
#include <Logging.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine {
	namespace Graphics {
		
		OgrePointLightComponentDescriptor OgrePointLightDescriptorParser::parse ( const UnknownEngine::Core::Properties& props )
		{
			OgrePointLightComponentDescriptor desc;
			
			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				props,
				{
					{
						"InitialTransform",
						PropertiesParser::ExternalParserOptionalNestedValue<Math::Transform, InitialTransformSectionParser>
						(desc.initial_transform)
					},
					{
						"LightSettings",
						PropertiesParser::ExternalParserOptionalNestedValue<OgreLightSettings, OgreLightSettingsParser>
						(desc.light_settings)
					},
					{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity>(desc.log_level)},
					{"transform_provider_name", PropertiesParser::OptionalValue<std::string>([&desc](const std::string& value){
						desc.transform_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
					}
					)}
				}
			);
			
			return desc;
		}

	}
}