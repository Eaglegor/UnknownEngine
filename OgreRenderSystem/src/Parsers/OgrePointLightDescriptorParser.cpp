#include <Parsers/OgrePointLightDescriptorParser.h>
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

			namespace OPTIONS
			{
				const std::string POSITION = "position"; // optional
				const std::string ORIENTATION = "orientation_quat"; // optional
			}
		}
		
		namespace LIGHT_SETTINGS
		{
			const std::string SECTION_NAME = "LightSettings";
			
			namespace OPTIONS
			{
				const std::string INTENSITY = "intensity";
				const std::string DIFFUSE_COLOR = "diffuse_color";
				const std::string SPECULAR_COLOR = "specular_color";
				const std::string CAST_SHADOWS = "cast_shadows";
			}
			
			
			namespace ATTENUATION
			{
				const std::string SECTION_NAME = "Attenuation";
				
				const std::string RANGE = "Range";
				const std::string CONSTANT = "Constant";
				const std::string LINEAR = "Linear";
				const std::string QUADRATIC = "Quadratic";
			}
		}
		
		OgrePointLightComponent::Descriptor OgrePointLightDescriptorParser::parse ( const UnknownEngine::Core::Properties& props )
		{
			OgrePointLightComponent::Descriptor desc;
			
			OptionalOptionsSection light_settings_section = props.get_optional<Core::Properties>(LIGHT_SETTINGS::SECTION_NAME);
			if(light_settings_section.is_initialized())
			{
				//OptionalStringOption attenuation = light_settings_section->get_optional<std::string>(LIGHT_SETTINGS::OPTIONS::ATTENUATION);
				//if(attenuation.is_initialized()) desc.attenuation = boost::lexical_cast<Math::Scalar>(attenuation.get());
					
				OptionalStringOption intensity = light_settings_section->get_optional<std::string>(LIGHT_SETTINGS::OPTIONS::INTENSITY);
				if(intensity.is_initialized()) desc.intensity = boost::lexical_cast<Math::Scalar>(intensity.get());
				
				OptionalStringOption diffuse_color = light_settings_section->get_optional<std::string>(LIGHT_SETTINGS::OPTIONS::DIFFUSE_COLOR);
				if( diffuse_color.is_initialized()) desc.diffuse_color = Utils::Vector3Parser::parse( diffuse_color.get() ) ;
				
				OptionalStringOption specular_color = light_settings_section->get_optional<std::string>(LIGHT_SETTINGS::OPTIONS::SPECULAR_COLOR);
				if( specular_color.is_initialized()) desc.specular_color = Utils::Vector3Parser::parse( specular_color.get() ) ;
			}
			
			OptionalOptionsSection initial_transform_section = props.get_optional<Core::Properties>( INITIAL_TRANSFORM_SECTION::SECTION_NAME );
			if ( initial_transform_section.is_initialized() )
			{
				OptionalStringOption initial_position = initial_transform_section->get_optional<std::string> ( INITIAL_TRANSFORM_SECTION::OPTIONS::POSITION );
				if ( initial_position.is_initialized() ) desc.initial_transform.setPosition ( Utils::Vector3Parser::parse ( initial_position.get() ) );

				OptionalStringOption initial_orientation_quat = initial_transform_section->get_optional<std::string> ( INITIAL_TRANSFORM_SECTION::OPTIONS::ORIENTATION );
				if ( initial_orientation_quat.is_initialized() ) desc.initial_transform.setOrientation ( Utils::QuaternionParser::parse ( initial_orientation_quat.get() ) );
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