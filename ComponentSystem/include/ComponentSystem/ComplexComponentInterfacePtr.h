#pragma once

#include <ComponentSystem/ComponentCast.h>
#include <ComponentSystem/ComponentsManager.h>
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

			template<typename U, typename... UU>
			bool fillInternalTuple(IComponent* component)
			{
				U* internal_interface_pointer = component_cast<U*>(component)
				if(internal_interface_pointer == nullptr) return false;
				std::get<U*>(internal_interface_pointers) = internal_interface_pointer;
				return fillInternalTuple<UU...>(component);
			}
			
			template<typename U, typename... UU>
			void resetInternalTuple()
			{
				std::get<U*>(internal_interface_pointers) = nullptr;
				resetInternalTuple<UU...>();
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
			getInterface()
			{
				return std::get<U*>(internal_interface_pointers);
			}
			
			operator bool()
			{
				if(internal_interface_pointer) return true;
				return false;
			}
			
		private:
			bool is_initialized;
			std::tuple<TT*...> internal_interface_pointers;
			IComponent* internal_component_pointer;
			
		};
	}
}