#pragma once

#include <ComponentSystem/IComponent.h>
#include <ComponentSystem/ComponentType.h>

namespace UnknownEngine
{
	template<typename T>
	T component_cast(Core::IComponent* component)
	{
		static_assert(std::is_pointer<T>::value, "Only component pointers may be used with component_cast");

		typedef std::remove_pointer<T>::type RawTargetType;
		static_assert(std::is_base_of<Core::IComponent, RawTargetType>::value, "Only components may be used with component_cast");

		if(component == nullptr) return nullptr;
		
		if(component->getType().is(T::getType()))
		{
			return static_cast<T>(component);
		}
		else 
		{
			return nullptr;
		}
		
	}
}