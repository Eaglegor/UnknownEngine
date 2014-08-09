/*
 * OptionsParser.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <boost/property_tree/ptree_fwd.hpp>
#include <Properties/Properties.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Loader
	{

		class ConstantsHolder;
		class IDataProvider;

		class OptionsParser
		{
			public:
				
				UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDataProviderFound);
				
				OptionsParser();
				virtual ~OptionsParser();

				static const Core::Properties parseOptions ( const boost::property_tree::ptree& options_node, const UnknownEngine::Loader::ConstantsHolder* constants, std::unordered_map< std::string, UnknownEngine::Loader::IDataProvider* >* data_providers_map = nullptr );

			private:
				static const Core::Properties parseOptionsSection ( const boost::property_tree::ptree &options_node, const ConstantsHolder* constants, std::unordered_map<std::string, IDataProvider*> *data_providers_map );
				static std::string parseSingleOption ( const boost::property_tree::ptree &options_node, const ConstantsHolder* constants );
		};

	} /* namespace Loader */
} /* namespace UnknownEngine */
