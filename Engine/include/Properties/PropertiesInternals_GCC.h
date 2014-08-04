#pragma once

/*
 * PropertiesSupportedTypes.h
 *
 *  Created on: 20 июня 2014 г.
 *      Author: Eaglegor
 */

#include <unordered_map>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/any.hpp>

namespace UnknownEngine
{
	namespace Core
	{

		/// Internal properties map implementation
		template<typename K>
		class PropertiesInternals
		{
			private:
				template<typename V>
				struct pv_pair
				{
						typedef boost::fusion::pair<V, std::unordered_map<K, V> > type;
				};

			public:
				typedef typename boost::fusion::map<
						typename pv_pair<float>::type,
						typename pv_pair<int>::type,
						typename pv_pair<bool>::type,
						typename pv_pair<std::string>::type,
						typename pv_pair<boost::any>::type> MapType;
		};

		/// List of types for which to use a separate maps
		template<typename V>
		using NotAnyPropertyTypes = typename std::integral_constant <
		bool,
		std::is_same<V, float>::value ||
		std::is_same<V, int>::value ||
		std::is_same<V, bool>::value ||
		std::is_same<V, std::string>::value
		>;

		/// List of types for which to use boost::any map with any_cast
		template<typename V>
		using AnyPropertyType = typename std::is_same < std::false_type, NotAnyPropertyTypes<V> >;

	}
}