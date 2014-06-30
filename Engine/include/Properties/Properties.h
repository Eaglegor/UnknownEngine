#pragma once
/*
 * Properties.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <unordered_map>
#include <string>
#include <InlineSpecification.h>

#include <Properties/PropertiesInternals.h>
#include <boost/fusion/include/at_key.hpp>

#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		UNKNOWNENGINE_SIMPLE_EXCEPTION(PropertyNotFoundException);

		template<typename K>
		class PropertiesTree
		{
			private:
				typedef typename PropertiesInternals<K>::MapType InternalMapType;

			public:
				PropertiesTree (){}
				virtual ~PropertiesTree (){}

				template<typename V>
				UNKNOWNENGINE_INLINE
				const std::unordered_map<K, V>& getAllOfType () const
				{
					return boost::fusion::at_key<V>( values_map );
				}

				template<typename V>
				UNKNOWNENGINE_INLINE
				typename boost::enable_if<NotAnyPropertyTypes<V>, const V& >::type
				get ( K name ) const throw(PropertyNotFoundException)
				{
					const std::unordered_map<K, V>& values = getAllOfType<V>();
					const auto found = values.find( name );
					if ( found == values.end() ) throw PropertyNotFoundException("Can't find requested property");
					return found->second;
				}

				template<typename V>
				UNKNOWNENGINE_INLINE
				typename boost::enable_if<NotAnyPropertyTypes<V>, const V& >::type
				get ( K name, const V &default_value ) const
				{
					const std::unordered_map<K, V>& values = getAllOfType<V>();
					const auto found = values.find( name );
					if ( found == values.end() ) return default_value;
					return found->second;
				}

				template<typename V>
				UNKNOWNENGINE_INLINE
				typename boost::enable_if<AnyPropertyType<V>, const V& >::type
				get ( K name ) const throw(PropertyNotFoundException)
				{
					const std::unordered_map<K, boost::any>& values = getAllOfType<boost::any>();
					const auto found = values.find( name );
					if ( found == values.end() ) throw PropertyNotFoundException("Can't find requested property");
					return boost::any_cast<const V&>(found->second);
				}

				template<typename V>
				UNKNOWNENGINE_INLINE
				typename boost::enable_if<AnyPropertyType<V>, const V& >::type
				get ( K name, const V &default_value ) const
				{
					const std::unordered_map<K, boost::any>& values = getAllOfType<boost::any>();
					const auto found = values.find( name );
					if ( found == values.end() ) return default_value;
					return boost::any_cast<const V&>(found->second);
				}

				template<typename V>
				UNKNOWNENGINE_INLINE
				typename boost::enable_if<NotAnyPropertyTypes<V>, void >::type
				set ( K name, const V &value )
				{
					std::unordered_map<K, V>& values = const_cast<std::unordered_map<K, V>&>(getAllOfType<V>());
					values[name] = value;
				}

				template<typename V>
				UNKNOWNENGINE_INLINE
				typename boost::enable_if<AnyPropertyType<V>, void >::type
				set ( K name, const V &value )
				{
					std::unordered_map<K, boost::any>& values = const_cast<std::unordered_map<K, boost::any>&>(getAllOfType<boost::any>());
					values[name] = value;
				}

			private:
				InternalMapType values_map;

		};

		class Properties: public PropertiesTree<std::string>{};

	} /* namespace Core */
} /* namespace UnknownEngine */
