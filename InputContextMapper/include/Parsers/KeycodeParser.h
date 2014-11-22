#pragma once

#include <string>
#include <Keys.h>
#include <unordered_map>
#include <Exception.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		class KeycodeParser
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(UnknownStringKeyCode);
			
			KeycodeParser();
			Key parse(const std::string &value) const;
			
		private:
			std::unordered_map<std::string, Key> mapping;
		};

	}
}