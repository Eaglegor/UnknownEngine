#pragma once

/*
 * PropertiesSupportedTypes.h
 *
 *  Created on: 20 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <map>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/any.hpp>

namespace UnknownEngine
{
	namespace Core
	{
		template<typename K = std::string>
		class PropertiesInternals
		{
			private:
				template<typename V>
				struct pv_pair
				{
						typedef boost::fusion::pair<V, std::map<K, V> > type;
				};

			public:
				typedef typename boost::fusion::map<typename pv_pair<float>::type, typename pv_pair<int>::type, typename pv_pair<std::string>::type, typename pv_pair<boost::any>::type > MapType;

		};

	}
}
