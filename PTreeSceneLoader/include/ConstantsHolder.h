#pragma once

#include <map>
#include <stack>

#include <InlineSpecification.h>

namespace boost
{
	namespace property_tree
	{
		class ptree;
	}
}

namespace UnknownEngine
{
	namespace Loader
	{

		class ConstantsHolder
		{
			public:

				ConstantsHolder();

				virtual ~ConstantsHolder();

				void pushConstantsLayer(const boost::property_tree::ptree &root_node);
				void popConstantsLayer();
				
				std::string applyConstants(const std::string &input_value);

			private:
				typedef std::map<std::string, std::string> ConstantsMap;
				std::stack<ConstantsMap> constants_maps;
				
		};

	} /* namespace Loader */
} /* namespace UnknownEngine */

