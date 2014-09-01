#pragma once

#include <Exception.h>
#include <Vectors/Vector4.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine
{
	namespace Utils
	{
		class Vector4Parser
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION ( Vector4ParseError );

				static Math::Vector4 parse ( const std::string &input ) 
				{
					std::vector<std::string> split_value;
					boost::algorithm::split ( split_value, input, boost::algorithm::is_any_of ( "(,: )" ), boost::algorithm::token_compress_on );
					if ( split_value.size() != 10 || split_value[0] != "Vector4" ) throw Vector4ParseError ( "Invalid Vector4 format. Expected: 'Vector4(x:1.4, y:0, z:-55, w:4)'. Got: " + input );

					Math::Vector4 result;

					bool x = false, y = false, z = false, w = false;

					for ( size_t i = 1; i < 9; i += 2 )
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
						if ( split_value[i] == "w" )
						{
							result.setW ( boost::lexical_cast<Math::Scalar> ( split_value[i + 1] ) );
							w = true;
						}
					}

					if ( !x ) throw Vector4ParseError ( "Invalid Vector4 format. 'x' value is not set. Got: " + input );
					if ( !y ) throw Vector4ParseError ( "Invalid Vector4 format. 'y' value is not set. Got: " + input );
					if ( !z ) throw Vector4ParseError ( "Invalid Vector4 format. 'z' value is not set. Got: " + input );
					if ( !w ) throw Vector4ParseError ( "Invalid Vector4 format. 'w' value is not set. Got: " + input );

					return result;
				}
		};
	}
}
