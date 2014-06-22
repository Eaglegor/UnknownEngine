/*
 * EntitiesParser.h
 *
 *  Created on: 22 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#ifndef ENTITIESPARSER_H_
#define ENTITIESPARSER_H_

#include <boost/property_tree/ptree.hpp>

namespace UnknownEngine
{

	namespace Core
	{
		class ComponentsManager;
	}

	namespace Loader
	{

		class TemplatesManager;
		class ConstantsHolder;

		class EntitiesLoader
		{
			public:
				EntitiesLoader(Core::ComponentsManager* components_manager, TemplatesManager* templates_manager, ConstantsHolder* constants_holder) :
						components_manager(components_manager), templates_manager(templates_manager), constants_holder(constants_holder)
				{
				}

				virtual ~EntitiesLoader();

				void loadEntities(boost::property_tree::ptree)
				{
				}

			private:
				Core::ComponentsManager* components_manager;
				TemplatesManager* templates_manager;
				ConstantsHolder* constants_holder;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* ENTITIESPARSER_H_ */
