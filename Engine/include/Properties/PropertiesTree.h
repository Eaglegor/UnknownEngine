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

#include <boost/optional.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>

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
		 * We use boost::variant to hold options. There are some primitive variant types (int, float, bool, string),
		 * the PropertyTree type to store children and boost::any type to store anything else. All unknown types are
		 * implicitly (for user) converted to / from boost::any when setting / getting.
		 *
		 */
		template<typename K>
		class PropertiesTree
		{
		private:
			typedef PropertiesTree<K> self_type;
			typedef boost::variant<int, float, std::string, bool, boost::recursive_wrapper<self_type>, boost::any> VariantType;
			
		public:
			
			UNKNOWNENGINE_INLINE
			template<typename V>
			const V& get(const K& name) const throw (PropertyNotFoundException)
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) throw PropertyNotFoundException("Can't find requested property: " + name);
				return *pointer;
			}
			
			UNKNOWNENGINE_INLINE
			template<typename V>
			const V& get(const K& name, const V& default_value) const
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) return default_value;
				return *pointer;
			}
			
			UNKNOWNENGINE_INLINE
			template<typename V>
			const boost::optional<const V&> get_optional(const K& name) const
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) return boost::optional<const V&>();
				return boost::optional<const V&>(*pointer);
			}
			
			UNKNOWNENGINE_INLINE
			template<typename V>
			const V* get_pointer(const K& name) const
			{
				const auto &iter = values.find(name);
				if(iter == values.end()) return nullptr;
				const V* pointer = boost::get<V>(&iter->second);
				if(pointer == nullptr)
				{
					const boost::any* any_val_pointer = boost::get<boost::any>(&iter->second);
					pointer = boost::any_cast<V>(any_val_pointer);
				}
				return pointer;
			}
			
			UNKNOWNENGINE_INLINE
			self_type& get_child(const K& name)
			{
				self_type* pointer = get_pointer<self_type>(name);
				if(pointer == nullptr) throw PropertyNotFoundException("Can't find requested child property: " + name);
				return *pointer;
			}
			
			UNKNOWNENGINE_INLINE
			boost::optional<self_type&> get_child_optional(const K& name)
			{
				self_type* pointer = get_pointer<self_type>(name);
				if(pointer == nullptr) return boost::optional<self_type&>();
				return boost::optional<self_type>(*pointer);
			}
			
			UNKNOWNENGINE_INLINE
			template<typename V>
			void set(const K& name, const V& value)
			{
				values[name] = value;
			}
			
		private:
			std::unordered_map<K, VariantType> values;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */