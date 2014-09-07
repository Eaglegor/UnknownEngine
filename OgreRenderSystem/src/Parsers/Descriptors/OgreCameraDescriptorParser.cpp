#include <stdafx.h>

#include <Parsers/Descriptors/OgreCameraDescriptorParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <CommonParsers/PropertiesParser.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreCameraComponentDescriptor OgreCameraDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreCameraComponentDescriptor desc;
			
			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				properties,
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
								{"initial_look_at", PropertiesParser::OptionalValue<Math::Vector3>( desc.initial_look_at )}
							}
						)
					},
					{"render_window_name", PropertiesParser::RequiredValue<std::string>(desc.render_window_name)},
					{"log_level", PropertiesParser::OptionalValue<Core::LogMessage::Severity>(desc.log_level)},
					{"near_clip_distance", PropertiesParser::OptionalValue<Math::Scalar>(desc.near_clip_distance)},
					{"far_clip_distance", PropertiesParser::OptionalValue<Math::Scalar>(desc.far_clip_distance)}
				}
			);
			
			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
