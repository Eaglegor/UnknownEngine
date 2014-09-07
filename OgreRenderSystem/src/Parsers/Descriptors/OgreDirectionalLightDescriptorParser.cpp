#include <stdafx.h>

#include <Parsers/Descriptors/OgreDirectionalLightDescriptorParser.h>
#include <Parsers/Sections/OgreLightSettingsParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <CommonParsers/PropertiesParser.h>
#include <LogHelper.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine {
	namespace Graphics {

		OgreDirectionalLightComponentDescriptor OgreDirectionalLightDescriptorParser::parse ( const UnknownEngine::Core::Properties& props )
		{
			OgreDirectionalLightComponentDescriptor desc;
			
			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				props,
				{
					{
						"InitialTransform",
						PropertiesParser::ExternalParserOptionalNestedValue<Core::Transform, InitialTransformSectionParser>
						(desc.initial_transform)
					},
					{
						"InitialTransform",
						PropertiesParser::OptionalNestedValue
						(
							{
								{"initial_look_at", PropertiesParser::OptionalValue<Math::Vector3>( desc.initial_look_at)},
								{"initial_direction", PropertiesParser::OptionalValue<Math::Vector3>( desc.initial_direction)}
							}
						)
					},
					{
						"LightSettings",
						PropertiesParser::ExternalParserOptionalNestedValue<OgreLightSettings, OgreLightSettingsParser>
						(desc.light_settings)
					},
					{"log_level", PropertiesParser::OptionalValue<Core::LogMessage::Severity>(desc.log_level)},
				}
			);
			
			return desc;
		}

	}
}