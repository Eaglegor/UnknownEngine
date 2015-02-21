#pragma once

#include <ComponentSystem/ComponentCast.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Core
	{
		template<typename T>
		class ComponentInterfacePtr
		{
		public:
			static_assert(std::is_base_of<IComponentInterface, T>::value, "Template parameter must be a component interface (Core::ComponentInterface)");
			
			ComponentInterfacePtr(IComponent* component)
			{
				internal_component_pointer = component;
				internal_interface_pointer = component_cast<T*>(internal_component_pointer);
				if(internal_interface_pointer)
				{
					ComponentsManager::getSingleton()->reserveComponent(internal_component_pointer);
				}
			}
			
			virtual ~ComponentInterfacePtr()
			{
				if(internal_interface_pointer)
				{
					ComponentsManager::getSingleton()->releaseComponent(internal_component_pointer);
				}
			}
			
			T* operator->()
			{
				return internal_interface_pointer;
			}
			
			operator bool()
			{
				if(internal_interface_pointer) return true;
				return false;
			}
			
		private:
			T* internal_interface_pointer;
			IComponent* internal_component_pointer;
			
		};
	}
}