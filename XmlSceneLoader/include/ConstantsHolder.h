/*
 * ConstantsHolder.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <map>
#include <list>

#include <InlineSpecification.h>
#include <boost/property_tree/ptree_fwd.hpp>
#include <SupportedTags.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Loader
	{

		class ConstantsHolder
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION ( LoaderConstantNotFoundException );

				ConstantsHolder()
				{
				}

				virtual ~ConstantsHolder()
				{
				}

				UNKNOWNENGINE_INLINE
				std::string getConstantValue ( const std::string &constant_name ) const 
				{
					for ( auto iter = constants_maps.rbegin(); iter != constants_maps.rend(); ++iter )
					{
						auto value = iter->find ( constant_name );
						if ( value != iter->end() )
						{
							return value->second;
						}
					}
					throw LoaderConstantNotFoundException ( "XmlSceneLoader: Can't find specified constant" );
				}

				UNKNOWNENGINE_INLINE
				void setConstantValue ( const std::string &constant_name, const std::string &value )
				{
					constants_maps.back() [constant_name] = value;
				}

				UNKNOWNENGINE_INLINE
				void pushScope()
				{
					constants_maps.emplace_back();
				}

				UNKNOWNENGINE_INLINE
				void popScope()
				{
					constants_maps.pop_back();
				}

				std::string applyPlaceholderConstants ( const std::string &input_string ) const;
				void parseAndSaveConstant ( const boost::property_tree::ptree &constant_node );

			private:
				typedef std::map<std::string, std::string> ConstantsMap;
				std::list<ConstantsMap> constants_maps;

		};

	} /* namespace Loader */
} /* namespace UnknownEngine */

