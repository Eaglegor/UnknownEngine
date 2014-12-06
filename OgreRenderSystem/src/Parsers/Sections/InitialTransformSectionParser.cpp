#include <stdafx.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <CommonParsers/PropertiesParser.h>
#include <Logging.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine {
	namespace Graphics {

		Math::Transform InitialTransformSectionParser::parse ( const UnknownEngine::Core::Properties& initial_transform_section )
		{
			Math::Transform result;
		
			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				initial_transform_section,
				{
					{"position", PropertiesParser::OptionalValue<Math::Vector3>( [&](const Math::Vector3& vec){result.setPosition(vec);} )},
					{"orientation_quat", PropertiesParser::OptionalValue<Math::Quaternion>( [&](const Math::Quaternion& quat){result.setOrientation(quat);} )}
				}
			);

			return result;
		}

	}
}