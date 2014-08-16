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
			typedef std::unordered_map<K, VariantType> MapType;
			
		public:
			
			/**
			 * @brief Iterator class to iterate over all properties of the specified type
			 */
			template<typename V>
			class Iterator
			{
			public:
				
				Iterator():
				internal_pointer(nullptr)
				{}
				
				explicit Iterator(PropertiesTree<K>* tree_to_iterate):
				tree_to_iterate(tree_to_iterate),
				internal_iter(tree_to_iterate->values.begin()),
				internal_pointer(nullptr)
				{
					findNext();
				};
				
				Iterator(const Iterator<V> &iter):
				tree_to_iterate(iter.tree_to_iterate), 
				internal_iter(iter.internal_iter),
				internal_pointer(nullptr)
				{};
				
				std::pair<K, V>& operator*()
				{
					return *internal_pointer;
				}
				
				const std::pair<K, V>& operator*() const
				{
					return *internal_pointer;
				}

				Iterator<V>& operator++()
				{
					findNext();
					return *this;
				}
				
				Iterator<V>& operator++(int)
				{
					Iterator<V> result(*this);
					findNext();
					return result;
				}
				
				bool operator==(const Iterator<V>& rhs)
				{
					return internal_iter == rhs.internal_iter;
				}
				
				Iterator<V>& operator=(const Iterator<V>& rhs)
				{
					this->internal_iter = rhs.intenal_iter;
					this->tree_to_iterate = rhs.map_to_iterate;
				}
				
			private:

				
				void findNext()
				{
					bool found = false;
					while(!found && internal_iter != tree_to_iterate->end())
					{
						++internal_iter;
						V* pointer = boost::get<V>(&internal_iter->second);
						if(pointer == nullptr)
						{
							const boost::any* any_val_pointer = boost::get<boost::any>(&internal_iter->second);
							pointer = boost::any_cast<V>(any_val_pointer);
						}
						found = (pointer != nullptr);
						if(found) internal_pointer = &(*internal_iter);
					}
				}
				
				std::pair<K, V>* internal_pointer;
				PropertiesTree<K>* tree_to_iterate;
				
				typedef typename PropertiesTree<K>::MapType::iterator InternalIteratorType;
				
				InternalIteratorType internal_iter;
			};
			
			/**
			* @brief Returns a value of specified type or throws exception
			* @param name - key of property to get
			* @return const reference to the property value
			* @throw PropertyNotFoundException - is thrown if no property with given name is found
			*/
			template<typename V>
			UNKNOWNENGINE_INLINE
			const V& get(const K& name) const throw (PropertyNotFoundException)
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) throw PropertyNotFoundException("Can't find requested property: " + name);
				return *pointer;
			}
			
			/**
			* @brief Returns a value of specified type or default value
			* @param name - key of property to get
			* @return const reference to the property value or default value if property not found
			*/
			template<typename V>
			UNKNOWNENGINE_INLINE
			const V& get(const K& name, const V& default_value) const
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) return default_value;
				return *pointer;
			}
			
			/**
			* @brief Returns boost::optional optionally containing requested property value
			* @param name - key of property to get
			* @return boost::optional containing const reference to the requested value. Is empty if no property is found by key.
			*/
			template<typename V>
			UNKNOWNENGINE_INLINE
			const boost::optional<const V&> get_optional(const K& name) const
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) return boost::optional<const V&>();
				return boost::optional<const V&>(*pointer);
			}
			
			/**
			* @brief Returns a pointer to the value of specified type or nullptr
			* @param name - key of property to get
			* @return Const pointer to the requested value or nullptr if property is not found by key
			*/
			template<typename V>
			UNKNOWNENGINE_INLINE
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
			
			/**
			* @brief Returns nested properties tree or throws exception
			* @param name - key of nested tree to get
			* @return const reference to the nested property tree
			* @throw PropertyNotFoundException - is thrown if no child with given name is found
			*/
			UNKNOWNENGINE_INLINE
			self_type& get_child(const K& name)
			{
				self_type* pointer = get_child_pointer(name);
				if(pointer == nullptr) throw PropertyNotFoundException("Can't find requested child property: " + name);
				return *pointer;
			}
			
			/**
			* @brief Returns nested properties tree or empty boost::optional
			* @param name - key of nested tree to get
			* @return boost::optional containing const reference to the requested child. Is empty if no child is found by key.
			*/
			UNKNOWNENGINE_INLINE
			boost::optional<self_type&> get_child_optional(const K& name)
			{
				self_type* pointer = get_child_pointer(name);
				if(pointer == nullptr) return boost::optional<self_type&>();
				return boost::optional<self_type>(*pointer);
			}
			
			/**
			* @brief Returns a pointer to the child or nullptr
			* @param name - key of child to get
			* @return Pointer to the requested child or nullptr if child is not found by key
			*/
			UNKNOWNENGINE_INLINE
			self_type* get_child_pointer(const K& name)
			{
				return const_cast<self_type*>(get_pointer<self_type>(name));
			}

			/**
			* @brief Sets the property value
			* @param name - key of property to set
			* @param value - new value of property
			*/
			template<typename V>
			UNKNOWNENGINE_INLINE
			void set(const K& name, const V& value)
			{
				values[name] = value;
			}
			
			/**
			 * @brief Returns the iterator pointing to the first value of specified type
			 */
			template<typename V>
			UNKNOWNENGINE_INLINE
			Iterator<V> begin()
			{
				return Iterator<V>(&values);
			}
			
			/**
			 * @brief Returns the iterator pointing to the end of properties map
			 */
			template<typename V>
			UNKNOWNENGINE_INLINE
			Iterator<V> end()
			{
				return Iterator<V>(&values, values.end());
			}
			
		private:
			template<typename V> friend class Iterator;
			MapType values;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */