#include <stdafx.h>

#include <Parsers/Descriptors/OgreCameraDescriptorParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
		typedef boost::optional<const std::string&> OptionalStringOption;

		namespace GLOBAL_OPTIONS
		{
			const std::string LOG_LEVEL = "log_level"; // optional
		}

		namespace INITIAL_TRANSFORM_SECTION
		{
			const std::string SECTION_NAME = "InitialTransform"; // optional

			namespace OPTIONS
			{
				const std::string LOOK_AT = "look_at"; // optional
			}
		}
		
		OgreCameraComponent::Descriptor OgreCameraDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreCameraComponent::Descriptor desc;
			
			OptionalOptionsSection initial_transform_section = properties.get_optional<Core::Properties>( INITIAL_TRANSFORM_SECTION::SECTION_NAME );
			if ( initial_transform_section.is_initialized() )
			{
				desc.initial_transform = InitialTransformSectionParser::parse(initial_transform_section.get());
				
				OptionalStringOption initial_look_at = initial_transform_section->get_optional<std::string> ( INITIAL_TRANSFORM_SECTION::OPTIONS::LOOK_AT );
				if ( initial_look_at.is_initialized() ) desc.initial_look_at = Utils::Vector3Parser::parse ( initial_look_at.get() );
			}
			
			OptionalStringOption log_level = properties.get_optional<std::string>(GLOBAL_OPTIONS::LOG_LEVEL);
			if(log_level.is_initialized())
			{
				desc.log_level = Core::LogHelper::parseLogLevel(log_level.get());
			}
			
			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
