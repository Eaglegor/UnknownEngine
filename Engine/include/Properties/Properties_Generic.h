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
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/property_tree/ptree.hpp>
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
			typedef boost::variant<int, float, std::string, bool, boost::any> VariantType;
			typedef PropertiesTree<K> self_type;
			
		public:
			
			template<typename V>
			const V& get(const K& name) const throw (PropertyNotFoundException)
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) throw PropertyNotFoundException("Can't find requested property: " + name);
				return *pointer;
			}
			
			template<typename V>
			const V& get(const K& name, const V& default_value) const
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) return default_value;
				return *pointer;
			}
			
			template<typename V>
			const boost::optional<const V&> get_optional(const K& name) const
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) return boost::optional<const V&>();
				return boost::optional<const V&>(*pointer);
			}
			
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
			
			self_type& get_child(const K& name)
			{
				self_type* pointer = get_child_pointer(name);
				if(pointer == nullptr) throw PropertyNotFoundException("Can't find requested child property: " + name);
				return *pointer;
			}
			
			boost::optional<self_type&> get_child_optional(const K& name)
			{
				self_type* pointer = get_child_pointer(name);
				if(pointer == nullptr) return boost::optional<self_type&>();
				return boost::optional<self_type>(*pointer);
			}
			
			self_type* get_child_pointer(const K& name)
			{
				const auto &iter = children.find(name);
				if(iter==children.end()) return nullptr;
				return iter->second.get();
			}
			
			template<typename V>
			void set(const K& name, const V& value)
			{
				values[name] = value;
			}
			
		protected:
			struct Child
			{
				std::unique_ptr< PropertiesTree<K> > data;
				
				Child(const PropertiesTree<K>& rhs)
				{
					data.reset(new PropertiesTree<K>(rhs));
				}
				
				UNKNOWNENGINE_INLINE
				const PropertiesTree<K> *get(){
					return data.get();
				}
			};
			
		private:
			std::unordered_map<K, VariantType> values;
			std::unordered_map<K, Child > children;
		};
		
		/**
		 * @brief Property tree with string keys
		 */
		class Properties: public PropertiesTree<std::string> {};

	} /* namespace Core */
} /* namespace UnknownEngine */
