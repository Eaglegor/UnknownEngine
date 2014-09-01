#include <stdafx.h>
#include <Parsers/Sections/OgreColourValueParser.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		Ogre::ColourValue OgreColourValueParser::parse ( const std::string& input ) 
		{
			std::vector<std::string> split_value;
			boost::algorithm::split ( split_value, input, boost::algorithm::is_any_of ( "(,: )" ), boost::algorithm::token_compress_on );
			if ( (split_value.size() != 8 && split_value.size() != 10) || split_value[0] != "Colour" ) throw OgreColourValueParseError ( "Invalid Colour format. Expected: 'Colour(r:1.4, g:0, b:-55, a:43)'. Got: " + input );

			Ogre::Real rv;
			Ogre::Real gv;
			Ogre::Real bv;
			Ogre::Real av;

			bool r = false, g = false, b = false, a = false;

			for ( size_t i = 1; i < split_value.size(); i += 2 )
			{
				if ( split_value[i] == "r" )
				{
					rv =  boost::lexical_cast<Math::Scalar> ( split_value[i + 1] );
					r = true;
				}
				if ( split_value[i] == "g" )
				{
					gv = boost::lexical_cast<Math::Scalar> ( split_value[i + 1] );
					g = true;
				}
				if ( split_value[i] == "b" )
				{
					bv = boost::lexical_cast<Math::Scalar> ( split_value[i + 1] );
					b = true;
				}
				if ( split_value[i] == "a" )
				{
					av = boost::lexical_cast<Math::Scalar> ( split_value[i + 1] );
					a = true;
				}
			}

			if ( !r ) throw OgreColourValueParseError ( "Invalid Colour format. 'r' value not set. Got: " + input );
			if ( !g ) throw OgreColourValueParseError ( "Invalid Colour format. 'g' value not set. Got: " + input );
			if ( !b ) throw OgreColourValueParseError ( "Invalid Colour format. 'b' value not set. Got: " + input );
			if ( !a ) av = 1;
			
			return Ogre::ColourValue ( rv, gv, bv, av );
		}
	}
}