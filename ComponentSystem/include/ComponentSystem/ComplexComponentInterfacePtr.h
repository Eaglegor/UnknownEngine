#pragma once

#include <ComponentSystem/ComponentCast.h>
#include <ComponentSystem/ComponentsManager.h>
#include <type_traits>
#include <tuple>

namespace UnknownEngine
{
	namespace Core
	{
		template<typename... TT>
		class ComplexComponentInterfacePtr
		{
		private:
			template<typename U, typename...>
			struct are_component_interfaces : std::is_base_of<IComponentInterface, U>
			{};

			template<typename U, typename Y, typename... UU>
			struct are_component_interfaces <U, Y, UU...> : public std::integral_constant<bool, std::is_base_of<IComponentInterface, U>::value && are_component_interfaces<Y, UU...>::value>
			{};

			
			// ###############
			// From internet - awaiting for C++14 with std::get<T>
			//
			template <class U, std::size_t N, class... Args>
			struct get_number_of_element_from_tuple_by_type_impl
			{
				static_assert( N < sizeof...(TT), "Requested type is not a part of complex component interface pointer");
				static constexpr auto value = N;
			};
			
			template <class U, std::size_t N, class... Args>
			struct get_number_of_element_from_tuple_by_type_impl<U, N, U, Args...>
			{
				static constexpr auto value = N;
			};
			
			template <class U, std::size_t N, class R, class... Args>
			struct get_number_of_element_from_tuple_by_type_impl<U, N, R, Args...>
			{
				static constexpr auto value = get_number_of_element_from_tuple_by_type_impl<U, N + 1, Args...>::value;
			};
			
			template<typename U> 
			U& getTupleElementByType()
			{
				return std::get<get_number_of_element_from_tuple_by_type_impl<U, 0, TT*...>::value>(internal_interface_pointers);
			}
			
			// ###################
			
			template<typename U, typename V, typename... UU>
			bool fillInternalTuple(IComponent* component)
			{
				U* internal_interface_pointer = component_cast<U*>(component);
				if(internal_interface_pointer == nullptr) return false;
				getTupleElementByType<U*>() = internal_interface_pointer;
				return fillInternalTuple<V, UU...>(component);
			}
			
			template<typename U>
			bool fillInternalTuple(IComponent* component)
			{
				U* internal_interface_pointer = component_cast<U*>(component);
				if(internal_interface_pointer == nullptr) return false;
				getTupleElementByType<U*>() = internal_interface_pointer;
				return true;
			}
			
			template<typename U>
			void resetInternalTuple()
			{
				getTupleElementByType<U*>() = nullptr;
			}
			
			template<typename U, typename V, typename... UU>
			void resetInternalTuple()
			{
				getTupleElementByType<U*>() = nullptr;
				resetInternalTuple<V, UU...>();
			}
			
		public:
			static_assert(are_component_interfaces<TT...>::value, "Template parameters must all be component interfaces (Core::ComponentInterface)");
			
			ComplexComponentInterfacePtr(IComponent* component):
			is_initialized(false)
			{
				internal_component_pointer = component;
				is_initialized = fillInternalTuple<TT...>(internal_component_pointer);
				if(is_initialized)
				{
					ComponentsManager::getSingleton()->reserveComponent(internal_component_pointer);
				}
				else
				{
					resetInternalTuple<TT...>();
				}
			}
			
			virtual ~ComplexComponentInterfacePtr()
			{
				if(is_initialized)
				{
					ComponentsManager::getSingleton()->releaseComponent(internal_component_pointer);
				}
			}
			
			template<typename U>
			U* getInterface()
			{
				return getTupleElementByType<U*>();
			}
			
			operator bool()
			{
				return is_initialized;
			}
			
		private:
			bool is_initialized;
			std::tuple<TT*...> internal_interface_pointers;
			IComponent* internal_component_pointer;
			
		};
	}
}