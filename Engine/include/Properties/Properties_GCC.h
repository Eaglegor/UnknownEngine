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

#include <Properties/PropertiesInternals_GCC.h>
#include <boost/fusion/include/at_key.hpp>

#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Is thrown when requested a non-existing property and no default value is provided
		 */
		UNKNOWNENGINE_SIMPLE_EXCEPTION(PropertyNotFoundException);

		/**
		 * @brief The properties map able to hold any value.
		 *
		 * \tparam K - Key type
		 *
		 * The main purpose of designing such class is the need for data holder for messages sent over a message bus.
		 * Because we don't know which data we will need, we want to hold any possible type
		 * The main concept is to get a stored data type with a templated get<> and set the data with a templated set<>.
		 *
		 * While we can hold any data we can hold the PropertiesTree itself - so it really becomes a hierarchical tree.
		 *
		 * ### Current implementation
		 * We use boost::any to hold the most of data types. To minimize boost::any overhead for some primitive types
		 * we store them in separate maps using boost::fusion to access this maps. All values that doesn't fit in separate
		 * types list are converted to boost::any when setting data and from boost::any when getting it.
		 *
		 *
		 */
		template<typename K>
		class PropertiesTree
		{
			private:
				typedef typename PropertiesInternals<K>::MapType InternalMapType;

			public:
				PropertiesTree (){}
				virtual ~PropertiesTree (){}

				/**
				 * @brief Returns all properties of type V
				 *
				 * Can return a map for only boost::any or allowed separate data types
				 *
				 * \tparam V - Value type
				 *
				 */
				template<typename V>
				UNKNOWNENGINE_INLINE
				const std::unordered_map<K, V>& getAllOfType () const
				{
					return boost::fusion::at_key<V>( values_map );
				}

				/**
				 * @brief Returns the property value by name
				 * @param name - Property name
				 *
				 * Uses separate maps
				 *
				 * \tparam V - Value type
				 *
				 * @throw PropertyNotFoundException - Is thrown if the property name wasn't found
				 *
				 */
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

				/**
				 * @brief Returns the property value by name or default value if propery not found
				 * @param name - Property name
				 *
				 * Uses separate maps
				 *
				 * \tparam V - Value type
				 *
				 */
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

				/**
				 * @brief Returns the property value by name
				 * @param name - Property name
				 *
				 * Uses boost::any map
				 *
				 * \tparam V - Value type
				 *
				 * @throw PropertyNotFoundException - Is thrown if the property name wasn't found
				 *
				 */
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

				/**
				 * @brief Returns the property value by name or default value if propery not found
				 * @param name - Property name
				 *
				 * Uses boost::any map
				 *
				 * \tparam V - Value type
				 *
				 */
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

				/**
				 * @brief Sets the property value by name
				 * @param name - Property name
				 * @param value - Property value
				 *
				 * Uses separate maps
				 *
				 * \tparam V - Value type
				 *
				 */
				template<typename V>
				UNKNOWNENGINE_INLINE
				typename boost::enable_if<NotAnyPropertyTypes<V>, void >::type
				set ( K name, const V &value )
				{
					std::unordered_map<K, V>& values = const_cast<std::unordered_map<K, V>&>(getAllOfType<V>());
					values[name] = value;
				}

				/**
				 * @brief Sets the property value by name
				 * @param name - Property name
				 * @param value - Property value
				 *
				 * Uses boost::any map
				 *
				 * \tparam V - Value type
				 *
				 */
				template<typename V>
				UNKNOWNENGINE_INLINE
				typename boost::enable_if<AnyPropertyType<V>, void >::type
				set ( K name, const V &value )
				{
					std::unordered_map<K, boost::any>& values = const_cast<std::unordered_map<K, boost::any>&>(getAllOfType<boost::any>());
					values[name] = value;
				}

			private:
				InternalMapType values_map; ///< Actual properties map implementation

		};

		/**
		 * @brief Property tree with string keys
		 */
		class Properties: public PropertiesTree<std::string>{};

	} /* namespace Core */
} /* namespace UnknownEngine */
