#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <LogHelper.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine {
	namespace Graphics {

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
		typedef boost::optional<const std::string&> OptionalStringOption;

		namespace INITIAL_TRANSFORM_SECTION
		{
			const std::string SECTION_NAME = "InitialTransform"; // optional

			namespace OPTIONS
			{
				const std::string POSITION = "position"; // optional
				const std::string ORIENTATION = "orientation_quat"; // optional
			}
		}
		
		Core::Transform InitialTransformSectionParser::parse ( const UnknownEngine::Core::Properties& initial_transform_section )
		{
			Core::Transform result;
			
			OptionalStringOption initial_position = initial_transform_section.get_optional<std::string> ( INITIAL_TRANSFORM_SECTION::OPTIONS::POSITION );
			if ( initial_position.is_initialized() ) result.setPosition ( Utils::Vector3Parser::parse ( initial_position.get() ) );

			OptionalStringOption initial_orientation_quat = initial_transform_section.get_optional<std::string> ( INITIAL_TRANSFORM_SECTION::OPTIONS::ORIENTATION );
			if ( initial_orientation_quat.is_initialized() ) result.setOrientation ( Utils::QuaternionParser::parse ( initial_orientation_quat.get() ) );
			
			return result;
		}

	}
}