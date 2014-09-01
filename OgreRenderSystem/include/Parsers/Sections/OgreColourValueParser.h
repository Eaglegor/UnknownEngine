#pragma once

#include <Exception.h>
#include <Vectors/Vector3.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <OgreColourValue.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreColourValueParser
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION ( OgreColourValueParseError );

				static Ogre::ColourValue parse ( const std::string &input ) ;
		};
	}
}
