#include <Parsers/Descriptors/OgreDirectionalLightDescriptorParser.h>
#include <Parsers/Sections/OgreLightSettingsParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <LogHelper.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine {
	namespace Graphics {

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
		typedef boost::optional<const std::string&> OptionalStringOption;
		
		namespace GLOBAL_OPTIONS
		{
			const std::string LOG_LEVEL = "log_level"; // optional
		}

		namespace INITIAL_TRANSFORM_SECTION
		{
			const std::string SECTION_NAME = "InitialTransform"; // optional
			
			const std::string INITIAL_LOOK_AT = "initial_look_at";
			const std::string INITIAL_DIRECTION = "initial_direction";
		}
		
		namespace LIGHT_SETTINGS
		{
			const std::string SECTION_NAME = "LightSettings";
		}
		
		OgreDirectionalLightComponent::Descriptor OgreDirectionalLightDescriptorParser::parse ( const UnknownEngine::Core::Properties& props )
		{
			OgreDirectionalLightComponent::Descriptor desc;
			
			OptionalOptionsSection light_settings_section = props.get_optional<Core::Properties>(LIGHT_SETTINGS::SECTION_NAME);
			if(light_settings_section.is_initialized())
			{
				desc.light_settings = OgreLightSettingsParser::parse(light_settings_section.get());
			}
			
			OptionalOptionsSection initial_transform_section = props.get_optional<Core::Properties>( INITIAL_TRANSFORM_SECTION::SECTION_NAME );
			if ( initial_transform_section.is_initialized() )
			{
				desc.initial_transform = InitialTransformSectionParser::parse(initial_transform_section.get());
				
				OptionalStringOption initial_look_at = initial_transform_section->get_optional<std::string> ( INITIAL_TRANSFORM_SECTION::INITIAL_LOOK_AT );
				if ( initial_look_at.is_initialized() ) desc.initial_look_at = Utils::Vector3Parser::parse ( initial_look_at.get() );
				
				OptionalStringOption initial_direction = initial_transform_section->get_optional<std::string> ( INITIAL_TRANSFORM_SECTION::INITIAL_DIRECTION );
				if ( initial_direction.is_initialized() ) desc.initial_direction = Utils::Vector3Parser::parse ( initial_direction.get() );
			}
			
			OptionalStringOption log_level = props.get_optional<std::string>(GLOBAL_OPTIONS::LOG_LEVEL);
			if(log_level.is_initialized())
			{
				desc.log_level = Core::LogHelper::parseLogLevel(log_level.get());
			}
			
			return desc;
		}

	}
}