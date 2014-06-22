/*
 * OptionsParser.h
 *
 *  Created on: 22 θώνÿ 2014 γ.
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

				static const Core::Properties<std::string> parseOptions(const boost::property_tree::ptree& options_node, ConstantsHolder* constants);

		};

	} /* namespace Loader */
} /* namespace UnknownEngine */

#endif /* OPTIONSPARSER_H_ */
