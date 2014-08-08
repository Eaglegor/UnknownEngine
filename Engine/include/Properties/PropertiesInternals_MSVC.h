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
#include <boost/optional.hpp>

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

		#define PROPERTIES_SEPARATE_MAP_GETTER(type) template<> const type &PropertiesTree<K>::get (const K &name, const type &default_value ) const { const std::unordered_map<K, type>& values = getAllOfType<type>(); const auto found = values.find( name ); if ( found == values.end() ) return default_value; return found->second; }
		#define PROPERTIES_SEPARATE_MAP_GETTER_THROWING(type) template<> const type &PropertiesTree<K>::get (const K &name ) const  throw(PropertyNotFoundException) { const std::unordered_map<K, type>& values = getAllOfType<type>(); const auto found = values.find( name ); if ( found == values.end() ) throw PropertyNotFoundException("Can't find requested property"); return found->second; }
		#define PROPERTIES_SEPARATE_MAP_GETTER_OPTIONAL(type) template<> boost::optional<const type &> PropertiesTree<K>::get_optional (const K &name ) const  throw(PropertyNotFoundException) { const std::unordered_map<K, type>& values = getAllOfType<type>(); const auto found = values.find( name ); if ( found == values.end() ) return boost::optional<const V&>(); return boost::optional<const V&>(found->second); }
		#define PROPERTIES_SEPARATE_MAP_SETTER(type) template<> void PropertiesTree<K>::set (const K &name, const type &value ) { std::unordered_map<K, type>& values = const_cast<std::unordered_map<K, type>&>(getAllOfType<type>()); values[name] = value; }


	}
}
