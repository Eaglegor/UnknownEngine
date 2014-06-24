/*
 * OptionsParser.cpp
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#include <ConstantsHolder.h>
#include <OptionsParser.h>
#include <SupportedTags.h>

namespace UnknownEngine
{
	namespace Loader
	{

		using namespace boost::property_tree;

		OptionsParser::OptionsParser()
		{
			// TODO Auto-generated constructor stub

		}

		OptionsParser::~OptionsParser()
		{
			// TODO Auto-generated destructor stub
		}

		const Core::Properties<std::string> OptionsParser::parseOptions(const ptree& options_node, const ConstantsHolder *constants)
		{
			return parseOptionsSection(options_node, constants);
		}

		const Core::Properties<std::string> OptionsParser::parseOptionsSection(const ptree &options_node, const ConstantsHolder *constants)
		{
			Core::Properties<std::string> result;
			for(const ptree::value_type &iter : options_node)
			{
				if(iter.first == Tags::OPTIONS_SECTION)
				{
					const std::string section_name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::OPTIONS_SECTION::NAME);
					result.set< Core::Properties<std::string> >(section_name, parseOptionsSection(iter.second, constants));
				}
				else if(iter.first == Tags::OPTION)
				{
					const std::string option_name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::OPTION::NAME);
					result.set<std::string> (option_name, parseSingleOption(iter.second, constants));
				}
			}
			return result;
		}

		std::string OptionsParser::parseSingleOption(const ptree &options_node, const ConstantsHolder *constants)
		{
			const std::string option_value = options_node.get_child(XMLATTR).get<std::string>(Attributes::OPTION::VALUE);
			if(constants!=nullptr){
				return constants->applyPlaceholderConstants(option_value);
			}
			return option_value;
		}

	} /* namespace Loader */
} /* namespace UnknownEngine */
