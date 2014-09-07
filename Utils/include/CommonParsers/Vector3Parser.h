#pragma once

#include <Exception.h>
#include <Vectors/Vector3.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine
{
	namespace Utils
	{
		class Vector3Parser
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION ( Vector3ParseError );

				static Math::Vector3 parse ( const std::string &input ) 
				{
					std::vector<std::string> split_value;
					boost::algorithm::split ( split_value, input, boost::algorithm::is_any_of ( "(,: )" ), boost::algorithm::token_compress_on );
					if ( split_value.size() != 8 || split_value[0] != "Vector3" ) throw Vector3ParseError ( "Invalid Vector3 format. Expected: 'Vector3(x:1.4, y:0, z:-55)'. Got: " + input );

					Math::Vector3 result;

					bool x = false, y = false, z = false;

					for ( size_t i = 1; i < 7; i += 2 )
					{
						if ( split_value[i] == "x" )
						{
							result.setX ( boost::lexical_cast<Math::Scalar> ( split_value[i + 1] ) );
							x = true;
						}
						if ( split_value[i] == "y" )
						{
							result.setY ( boost::lexical_cast<Math::Scalar> ( split_value[i + 1] ) );
							y = true;
						}
						if ( split_value[i] == "z" )
						{
							result.setZ ( boost::lexical_cast<Math::Scalar> ( split_value[i + 1] ) );
							z = true;
						}
					}

					if ( !x ) throw Vector3ParseError ( "Invalid Vector3 format. 'x' value is not set. Got: " + input );
					if ( !y ) throw Vector3ParseError ( "Invalid Vector3 format. 'y' value is not set. Got: " + input );
					if ( !z ) throw Vector3ParseError ( "Invalid Vector3 format. 'z' value is not set. Got: " + input );

					return result;
				}
		};
	}
}


namespace boost
{
	template<>
	UNKNOWNENGINE_INLINE
	UnknownEngine::Math::Vector3 lexical_cast<UnknownEngine::Math::Vector3, std::string>(const std::string& string_value)
	{
		return UnknownEngine::Utils::Vector3Parser::parse(string_value);
	}
}
