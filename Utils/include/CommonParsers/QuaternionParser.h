#pragma once

#include <Exception.h>
#include <Quaternion.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine
{
	namespace Utils
	{
		class QuaternionParser
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(QuaternionParseError);

			static Math::Quaternion parse(const std::string &input) throw(QuaternionParseError)
			{

				std::vector<std::string> split_value;
				boost::algorithm::split(split_value, input, boost::algorithm::is_any_of("(,: )"), boost::algorithm::token_compress_on);
				if(split_value.size() != 9 || split_value[0] != "Quaternion") throw QuaternionParseError("Invalid Quaternion format. Expected: 'Quaternion(x:1.4, y:0, z:-55, w:1)'. Got: " + input);

				Math::Quaternion result;

				bool x = false, y = false, z = false, w = false;

				for(size_t i = 1; i < 9; i+=2)
				{
					if(split_value[i] == "x")
					{
						result.setX(boost::lexical_cast<Math::Scalar>(split_value[i+1]));
						x = true;
					}
					if(split_value[i] == "y")
					{
						result.setY(boost::lexical_cast<Math::Scalar>(split_value[i+1]));
						y = true;
					}
					if(split_value[i] == "z")
					{
						result.setZ(boost::lexical_cast<Math::Scalar>(split_value[i+1]));
						z = true;
					}
					if(split_value[i] == "w")
					{
						result.setW(boost::lexical_cast<Math::Scalar>(split_value[i+1]));
						w = true;
					}
				}

				if(!x) throw QuaternionParseError("Invalid Quaternion format. 'x' value is not set. Got: " + input);
				if(!y) throw QuaternionParseError("Invalid Quaternion format. 'y' value is not set. Got: " + input);
				if(!z) throw QuaternionParseError("Invalid Quaternion format. 'z' value is not set. Got: " + input);
				if(!w) throw QuaternionParseError("Invalid Quaternion format. 'w' value is not set. Got: " + input);

				return result;
			}
		};
	}
}