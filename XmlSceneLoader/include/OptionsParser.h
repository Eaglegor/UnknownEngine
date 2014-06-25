/*
 * OptionsParser.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#ifndef OPTIONSPARSER_H_
#define OPTIONSPARSER_H_

#include <Properties/Properties.h>
#include <boost/property_tree/ptree.hpp>

namespace UnknownEngine
{
	namespace Loader
	{

		class ConstantsHolder;

		class OptionsParser
		{
			public:
				OptionsParser();
				virtual ~OptionsParser();

				static const Core::Properties parseOptions(const boost::property_tree::ptree& options_node, const ConstantsHolder* constants);

			private:
				static const Core::Properties parseOptionsSection(const boost::property_tree::ptree &options_node, const ConstantsHolder* constants);
				static std::string parseSingleOption(const boost::property_tree::ptree &options_node, const ConstantsHolder* constants);
		};

	} /* namespace Loader */
} /* namespace UnknownEngine */

#endif /* OPTIONSPARSER_H_ */
