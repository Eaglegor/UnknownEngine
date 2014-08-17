#include <Parsers/Descriptors/OgrePointLightDescriptorParser.h>
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
		}
		
		namespace LIGHT_SETTINGS
		{
			const std::string SECTION_NAME = "LightSettings";
		}
		
		OgrePointLightComponent::Descriptor OgrePointLightDescriptorParser::parse ( const UnknownEngine::Core::Properties& props )
		{
			OgrePointLightComponent::Descriptor desc;
			
			OptionalOptionsSection light_settings_section = props.get_optional<Core::Properties>(LIGHT_SETTINGS::SECTION_NAME);
			if(light_settings_section.is_initialized())
			{
				desc.light_settings = OgreLightSettingsParser::parse(light_settings_section.get());
			}
			
			OptionalOptionsSection initial_transform_section = props.get_optional<Core::Properties>( INITIAL_TRANSFORM_SECTION::SECTION_NAME );
			if ( initial_transform_section.is_initialized() )
			{
				desc.initial_transform = InitialTransformSectionParser::parse(initial_transform_section.get());
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