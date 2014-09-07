#include <stdafx.h>
#include <Parsers/Sections/OgreLightSettingsParser.h>
#include <Parsers/Sections/OgreColourValueParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <boost/lexical_cast.hpp>
#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <CommonParsers/PropertiesParser.h>
#include <Properties/Properties.h>

namespace UnknownEngine {
	namespace Graphics {

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
		typedef boost::optional<const std::string&> OptionalStringOption;

		namespace LIGHT_SETTINGS
		{
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
			
			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				light_settings_section,
				{
					{"intensity", PropertiesParser::OptionalValue<Math::Scalar>(light_settings.intensity)},
					{"diffuse_color", PropertiesParser::OptionalValue<Ogre::ColourValue>(light_settings.diffuse_color)},
					{"specular_color", PropertiesParser::OptionalValue<Ogre::ColourValue>(light_settings.specular_color)},
					{"cast_shadows", PropertiesParser::OptionalValue<bool>(light_settings.cast_shadows)}
				}
			);

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

			return light_settings;
		}

	}
}