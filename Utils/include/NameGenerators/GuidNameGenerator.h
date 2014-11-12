#pragma once

#include <NameGenerators/NameGenerator.h>
#include <string>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace UnknownEngine
{
	namespace Utils
	{
		class GuidNameGenerator : public NameGenerator
		{
		public:
			virtual std::string generateName()
			{
				return to_string(generator());
			}
			
		private:
			boost::uuids::random_generator generator;
		};
	}
}