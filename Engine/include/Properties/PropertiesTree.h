#pragma once

#include <unordered_map>
#include <string>
#include <InlineSpecification.h>

#include <boost/optional.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>

#include <vector>

#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		UNKNOWNENGINE_SIMPLE_EXCEPTION ( PropertyNotFoundException );

		template<typename K>
		class PropertiesTree
		{
		private:
			typedef PropertiesTree<K> self_type;
			typedef boost::variant<int, float, std::string, boost::recursive_wrapper<self_type>, std::vector<std::string>, std::vector<boost::recursive_wrapper<self_type>, boost::any> VariantType;
			typedef std::unordered_map<K, VariantType> MapType;
			
		public:
			template<typename V>
			class Iterator
			{
			public:
				
				Iterator(){}
				
				explicit Iterator(PropertiesTree<K>* tree_to_iterate):
				tree_to_iterate(tree_to_iterate),
				internal_iter(tree_to_iterate->values.begin())
				{
					findNext(true);
				};
				
				Iterator(const Iterator<V> &iter):
				tree_to_iterate(iter.tree_to_iterate), 
				internal_iter(iter.internal_iter),
				internal_pointer(iter.internal_pointer)
				{
				};
				
				std::pair<K, V*>& operator*()
				{
					return internal_pointer;
				}
				
				const std::pair<K, V*>& operator*() const
				{
					return internal_pointer;
				}

				std::pair<K, V*>* operator->()
				{
					return &internal_pointer;
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
				
				bool operator==(const Iterator<V>& rhs) const
				{
					return internal_iter == rhs.internal_iter;
				}
				
				bool operator!=(const Iterator<V>& rhs) const
				{
					return !(*this == rhs);
				}
				
				Iterator<V>& operator=(const Iterator<V>& rhs)
				{
					if(this == &rhs) return *this;
					this->internal_iter = rhs.internal_iter;
					this->tree_to_iterate = rhs.tree_to_iterate;
					this->internal_pointer = rhs.internal_pointer;
				}
				
			private:
				friend class PropertiesTree<K>;
				
				typedef typename PropertiesTree<K>::MapType::iterator InternalIteratorType;
				
				Iterator(PropertiesTree<K>* tree_to_iterate, InternalIteratorType initial_iter):
				tree_to_iterate(tree_to_iterate),
				internal_iter(initial_iter)
				{
				};
				
				void findNext(bool accept_current = false)
				{
					bool found = false;
					bool first_time = true;
					while(!found && internal_iter != tree_to_iterate->values.end())
					{
						if(!accept_current || !first_time)
						{
							++internal_iter;
						}
						if(internal_iter != tree_to_iterate->values.end())
						{
							V* pointer = boost::get<V>(&internal_iter->second);
							if(pointer == nullptr)
							{
								boost::any* any_val_pointer = boost::get<boost::any>(&internal_iter->second);
								pointer = boost::any_cast<V>(any_val_pointer);
							}
							found = (pointer != nullptr);
							if(found) 
							{
								internal_pointer.first = internal_iter->first;
								internal_pointer.second = pointer;
							}
						}
						first_time = false;
					}
				}
				
				std::pair<K, V*> internal_pointer;
				PropertiesTree<K>* tree_to_iterate;
				
				InternalIteratorType internal_iter;
			};

			template<typename V>
			UNKNOWNENGINE_INLINE
			const V& get(const K& name) const 
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) throw PropertyNotFoundException("Can't find requested property: " + name);
				return *pointer;
			}

			template<typename V>
			UNKNOWNENGINE_INLINE
			const V& get(const K& name, const V& default_value) const
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) return default_value;
				return *pointer;
			}

			template<typename V>
			UNKNOWNENGINE_INLINE
			const boost::optional<const V&> get_optional(const K& name) const
			{
				const V* pointer = get_pointer<V>(name);
				if(pointer == nullptr) return boost::optional<const V&>();
				return boost::optional<const V&>(*pointer);
			}

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

			UNKNOWNENGINE_INLINE
			self_type& get_child(const K& name)
			{
				self_type* pointer = get_child_pointer(name);
				if(pointer == nullptr) throw PropertyNotFoundException("Can't find requested child property: " + name);
				return *pointer;
			}
			

			UNKNOWNENGINE_INLINE
			boost::optional<self_type&> get_child_optional(const K& name)
			{
				self_type* pointer = get_child_pointer(name);
				if(pointer == nullptr) return boost::optional<self_type&>();
				return boost::optional<self_type>(*pointer);
			}

			UNKNOWNENGINE_INLINE
			self_type* get_child_pointer(const K& name)
			{
				return const_cast<self_type*>(get_pointer<self_type>(name));
			}

			template<typename V>
			UNKNOWNENGINE_INLINE
			void set(const K& name, const V& value)
			{
				values[name] = value;
			}
			
			template<typename V>
			UNKNOWNENGINE_INLINE
			Iterator<V> begin()
			{
				return Iterator<V>(this);
			}
			
			template<typename V>
			UNKNOWNENGINE_INLINE
			Iterator<V> end()
			{
				return Iterator<V>(this, values.end());
			}
			
		private:
			template<typename V> friend class Iterator;
			MapType values;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
