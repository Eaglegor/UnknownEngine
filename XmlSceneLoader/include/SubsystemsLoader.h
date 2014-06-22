/*
 * SubsystemsParser.h
 *
 *  Created on: 22 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#ifndef SUBSYSTEMSPARSER_H_
#define SUBSYSTEMSPARSER_H_

#include <boost/property_tree/ptree.hpp>

namespace UnknownEngine
{

	namespace Core
	{
		class PluginsManager;
	}

	namespace Loader
	{

		class TemplatesManager;
		class ConstantsHolder;

		class SubsystemsLoader
		{
			public:
				SubsystemsLoader(Core::PluginsManager* plugins_manager, TemplatesManager* templates_manager, ConstantsHolder* constants_holder) :
						plugins_manager(plugins_manager), templates_manager(templates_manager), constants_holder(constants_holder)
				{
				}
				virtual ~SubsystemsLoader();

				void loadSubsystems(const boost::property_tree::ptree &node);

			private:
				Core::PluginsManager* plugins_manager;
				TemplatesManager* templates_manager;
				ConstantsHolder* constants_holder;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* SUBSYSTEMSPARSER_H_ */
