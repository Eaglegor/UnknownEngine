#include <stdafx.h>

#include <Parsers/Descriptors/OgrePointLightDescriptorParser.h>
#include <Parsers/Sections/OgreLightSettingsParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <CommonParsers/PropertiesParser.h>
#include <LogHelper.h>
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
						PropertiesParser::ExternalParserOptionalNestedValue<Core::Transform, InitialTransformSectionParser>
						(desc.initial_transform)
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