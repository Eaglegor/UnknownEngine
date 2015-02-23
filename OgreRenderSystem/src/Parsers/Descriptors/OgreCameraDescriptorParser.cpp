#include <stdafx.h>

#include <Parsers/Descriptors/OgreCameraDescriptorParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <CommonParsers/PropertiesParser.h>
#include <Logging.h>
#include <ComponentSystem/ComponentsManager.h>

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
						PropertiesParser::ExternalParserOptionalNestedValue<Math::Transform, InitialTransformSectionParser>
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
					{"render_window_name", PropertiesParser::OptionalValue<std::string>([&desc](const std::string& value){
						desc.render_window = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
					})},
					{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity>(desc.log_level)},
					{"near_clip_distance", PropertiesParser::OptionalValue<Math::Scalar>(desc.near_clip_distance)},
					{"far_clip_distance", PropertiesParser::OptionalValue<Math::Scalar>(desc.far_clip_distance)}
				}
			);
			
			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
