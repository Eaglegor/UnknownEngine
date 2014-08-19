#include <Parsers/Sections/OgreLightSettingsParser.h>
#include <Parsers/Sections/OgreColourValueParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <boost/lexical_cast.hpp>
#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <Properties/Properties.h>

namespace UnknownEngine {
	namespace Graphics {

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
		typedef boost::optional<const std::string&> OptionalStringOption;

		namespace LIGHT_SETTINGS
		{
			const std::string SECTION_NAME = "LightSettings";
			
			const std::string INTENSITY = "intensity";
			const std::string DIFFUSE_COLOR = "diffuse_color";
			const std::string SPECULAR_COLOR = "specular_color";
			const std::string CAST_SHADOWS = "cast_shadows";
			
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
				
			OptionalStringOption intensity = light_settings_section.get_optional<std::string>(LIGHT_SETTINGS::INTENSITY);
			if(intensity.is_initialized()) light_settings.intensity = boost::lexical_cast<Math::Scalar>(intensity.get());
			
			OptionalStringOption diffuse_color = light_settings_section.get_optional<std::string>(LIGHT_SETTINGS::DIFFUSE_COLOR);
			if( diffuse_color.is_initialized()) light_settings.diffuse_color = OgreColourValueParser::parse( diffuse_color.get() ) ;
			
			OptionalStringOption specular_color = light_settings_section.get_optional<std::string>(LIGHT_SETTINGS::SPECULAR_COLOR);
			if( specular_color.is_initialized()) light_settings.specular_color = OgreColourValueParser::parse( specular_color.get() ) ;

			OptionalOptionsSection attenuation_section = light_settings_section.get_optional<Core::Properties>(LIGHT_SETTINGS::ATTENUATION::SECTION_NAME);
			if(attenuation_section.is_initialized())
			{
				OgreLightSettings::Attenuation attenuation;
				attenuation.range = attenuation_section->get<Math::Scalar>(LIGHT_SETTINGS::ATTENUATION::RANGE);
				attenuation.constant = attenuation_section->get<Math::Scalar>(LIGHT_SETTINGS::ATTENUATION::CONSTANT);
				attenuation.linear = attenuation_section->get<Math::Scalar>(LIGHT_SETTINGS::ATTENUATION::LINEAR);
				attenuation.quadratic = attenuation_section->get<Math::Scalar>(LIGHT_SETTINGS::ATTENUATION::QUADRATIC);
				light_settings.attenuation = attenuation;
			}
			
			OptionalStringOption cast_shadows = light_settings_section.get_optional<std::string>(LIGHT_SETTINGS::CAST_SHADOWS);
			if(cast_shadows.is_initialized()) light_settings.cast_shadows = boost::lexical_cast<bool>( cast_shadows.get() );
			
			return light_settings;
		}

	}
}