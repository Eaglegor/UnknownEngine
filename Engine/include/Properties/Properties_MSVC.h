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

#include <Properties/PropertiesInternals_MSVC.h>
#include <boost/fusion/include/at_key.hpp>

#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Is thrown when requested a non-existing property and no default value is provided
		 */
		UNKNOWNENGINE_SIMPLE_EXCEPTION ( PropertyNotFoundException );

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
					return boost::fusion::at_key<V> ( values_map );
				}

			public:
				PropertiesTree () {}
				virtual ~PropertiesTree () {}

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
				const V &get ( const K &name ) const throw ( PropertyNotFoundException )
				{
					const std::unordered_map<K, boost::any>& values = getAllOfType<boost::any>();
					const auto found = values.find ( name );
					if ( found == values.end() ) throw PropertyNotFoundException ( "Can't find requested property" );
					return boost::any_cast<const V&> ( found->second );
				}

				/**
				 * @brief Returns the property value by name or empty boost::optional if the key wasn't found
				 * @param name - Property name
				 *
				 * Uses boost::any map
				 *
				 * \tparam V - Value type
				 *
				 */
				template<typename V>
				UNKNOWNENGINE_INLINE
				boost::optional<const V&> get_optional ( const K &name ) const
				{
					const std::unordered_map<K, boost::any>& values = getAllOfType<boost::any>();
					const auto found = values.find ( name );
					if ( found == values.end() ) return boost::optional<const V&>();
					return boost::optional<const V&> ( boost::any_cast<const V&> ( found->second ) );
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
				const V &get ( const K &name, const V &default_value ) const
				{
					const std::unordered_map<K, boost::any>& values = getAllOfType<boost::any>();
					const auto found = values.find ( name );
					if ( found == values.end() ) return default_value;
					return boost::any_cast<const V&> ( found->second );
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
				void set ( const K &name, const V &value )
				{
					std::unordered_map<K, boost::any>& values = const_cast<std::unordered_map<K, boost::any>&> ( getAllOfType<boost::any>() );
					values[name] = value;
				}

				PROPERTIES_SEPARATE_MAP_GETTER ( int )
				PROPERTIES_SEPARATE_MAP_GETTER ( float )
				PROPERTIES_SEPARATE_MAP_GETTER ( std::string )
				PROPERTIES_SEPARATE_MAP_GETTER ( bool )

				PROPERTIES_SEPARATE_MAP_GETTER_THROWING ( int )
				PROPERTIES_SEPARATE_MAP_GETTER_THROWING ( float )
				PROPERTIES_SEPARATE_MAP_GETTER_THROWING ( std::string )
				PROPERTIES_SEPARATE_MAP_GETTER_THROWING ( bool )

				PROPERTIES_SEPARATE_MAP_GETTER_OPTIONAL ( int )
				PROPERTIES_SEPARATE_MAP_GETTER_OPTIONAL ( float )
				PROPERTIES_SEPARATE_MAP_GETTER_OPTIONAL ( std::string )
				PROPERTIES_SEPARATE_MAP_GETTER_OPTIONAL ( bool )

				PROPERTIES_SEPARATE_MAP_SETTER ( int )
				PROPERTIES_SEPARATE_MAP_SETTER ( float )
				PROPERTIES_SEPARATE_MAP_SETTER ( std::string )
				PROPERTIES_SEPARATE_MAP_SETTER ( bool )

			private:
				InternalMapType values_map; ///< Actual properties map implementation

		};

		/**
		 * @brief Property tree with string keys
		 */
		class Properties: public PropertiesTree<std::string> {};

	} /* namespace Core */
} /* namespace UnknownEngine */
