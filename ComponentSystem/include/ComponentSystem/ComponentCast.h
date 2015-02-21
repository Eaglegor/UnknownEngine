#pragma once

#include <ComponentSystem/IComponent.h>
#include <ComponentSystem/IComponentInterface.h>
#include <ComponentSystem/ComponentType.h>

namespace UnknownEngine
{
	template<typename T>
	T component_cast(Core::IComponent* component)
	{
		static_assert(std::is_pointer<T>::value, "Only component pointers may be used with component_cast");

		typedef typename std::remove_pointer<T>::type RawTargetType;
		static_assert(std::is_base_of<Core::IComponentInterface, RawTargetType>::value, "Components can only be cast to component interfaces");

		if(component == nullptr) return nullptr;
		
		Core::IComponentInterface* interface = component->getInterface(Core::ComponentType(RawTargetType::getTypeName()));
		if(interface == nullptr) return nullptr;
		else return static_cast<T>(interface);
	}
}