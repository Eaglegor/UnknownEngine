#pragma once
/*
 * Properties.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <map>
#include <string>
#include <InlineSpecification.h>

#include <Properties/PropertiesInternals.h>
#include <boost/fusion/include/at_key.hpp>

namespace UnknownEngine
{
	namespace Core
	{

		typedef std::exception PropertyNotFoundException;

		template<typename K = std::string>
		class Properties
		{
			private:
				typedef typename PropertiesInternals<K>::MapType InternalMapType;

			public:
				Properties (){}
				virtual ~Properties (){}

				template<typename V>
				UNKNOWNENGINE_INLINE
				const std::map<K, V>& getAllOfType () const
				{
					return boost::fusion::at_key<V>( values_map );
				}

				template<typename V>
				UNKNOWNENGINE_INLINE
				const V& get ( K name ) const throw(PropertyNotFoundException)
				{
					const std::map<K, V>& values = getAllOfType<V>();
					const auto found = values.find( name );
					if ( found == values.end() ) throw PropertyNotFoundException();
					return found->second;
				}

				template<typename V>
				UNKNOWNENGINE_INLINE
				const V& get ( K name, const V &default_value ) const
				{
					const std::map<K, V>& values = getAllOfType<V>();
					const auto found = values.find( name );
					if ( found == values.end() ) return default_value;
					return found->second;
				}

				template<typename V>
				UNKNOWNENGINE_INLINE
				void set ( K name, const V &value )
				{

				}

			private:
				InternalMapType values_map;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
