/*
 * OptionsParser.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <boost/property_tree/ptree_fwd.hpp>
#include <Properties/Properties.h>

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

				static const Core::Properties parseOptions ( const boost::property_tree::ptree& options_node, const ConstantsHolder* constants );

			private:
				static const Core::Properties parseOptionsSection ( const boost::property_tree::ptree &options_node, const ConstantsHolder* constants );
				static std::string parseSingleOption ( const boost::property_tree::ptree &options_node, const ConstantsHolder* constants );
		};

	} /* namespace Loader */
} /* namespace UnknownEngine */
