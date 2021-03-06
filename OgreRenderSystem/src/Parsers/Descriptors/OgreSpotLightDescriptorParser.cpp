#include <stdafx.h>

#include <Parsers/Descriptors/OgreSpotLightDescriptorParser.h>
#include <Parsers/Sections/OgreLightSettingsParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <CommonParsers/PropertiesParser.h>
#include <Logging.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine {
	namespace Graphics {

		OgreSpotLightComponentDescriptor OgreSpotLightDescriptorParser::parse ( const UnknownEngine::Core::Properties& props )
		{
			OgreSpotLightComponentDescriptor desc;
			
			using Utils::PropertiesParser;
			
			PropertiesParser::parse 
			(
				props,
				{
					{
						"LightSettings",
						PropertiesParser::ExternalParserOptionalNestedValue<OgreLightSettings, OgreLightSettingsParser>
						(desc.light_settings)
					},
					{
						"LightSettings",
						PropertiesParser::OptionalNestedValue
						(
						{
							{"spotlight_inner_angle", PropertiesParser::OptionalValue <Math::Scalar> (desc.inner_angle)},
							{"spotlight_outer_angle", PropertiesParser::OptionalValue <Math::Scalar> (desc.outer_angle)},
							{"spotlight_falloff", PropertiesParser::OptionalValue <Math::Scalar> (desc.falloff)}
						}
						)
					},
					{
						"InitialTransform",
						PropertiesParser::ExternalParserOptionalNestedValue<Math::Transform, InitialTransformSectionParser>
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