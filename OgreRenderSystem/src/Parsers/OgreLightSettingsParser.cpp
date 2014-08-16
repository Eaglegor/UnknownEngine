#include <Parsers/OgreLightSettingsParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine {
	namespace Graphics {

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
		typedef boost::optional<const std::string&> OptionalStringOption;

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
				
				const std::string RANGE = "range";
				const std::string CONSTANT = "constant";
				const std::string LINEAR = "linear";
				const std::string QUADRATIC = "quadratic";
			}
		}
		
		OgreLightSettings OgreLightSettingsParser::parse ( const Core::Properties& light_settings_section )
		{
			OgreLightSettings light_settings;
			
			//OptionalStringOption attenuation = light_settings_section->get_optional<std::string>(LIGHT_SETTINGS::OPTIONS::ATTENUATION);
			//if(attenuation.is_initialized()) desc.attenuation = boost::lexical_cast<Math::Scalar>(attenuation.get());
				
			OptionalStringOption intensity = light_settings_section.get_optional<std::string>(LIGHT_SETTINGS::OPTIONS::INTENSITY);
			if(intensity.is_initialized()) light_settings.intensity = boost::lexical_cast<Math::Scalar>(intensity.get());
			
			OptionalStringOption diffuse_color = light_settings_section.get_optional<std::string>(LIGHT_SETTINGS::OPTIONS::DIFFUSE_COLOR);
			if( diffuse_color.is_initialized()) light_settings.diffuse_color = Utils::Vector3Parser::parse( diffuse_color.get() ) ;
			
			OptionalStringOption specular_color = light_settings_section.get_optional<std::string>(LIGHT_SETTINGS::OPTIONS::SPECULAR_COLOR);
			if( specular_color.is_initialized()) light_settings.specular_color = Utils::Vector3Parser::parse( specular_color.get() ) ;

			return light_settings;
		}

	}
}