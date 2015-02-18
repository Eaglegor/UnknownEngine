#pragma once

#include <ComponentSystem/ComponentCast.h>
#include "ComponentsManager.h"

namespace UnknownEngine
{
	namespace Core
	{
		template<typename T>
		class ComponentPtr
		{
		public:
			static_assert(std::is_base_of<T, Core::IComponent>::value, "Only component types may be used with ComponentPtr");
			
			ComponentPtr(IComponent* component)
			{
				internal_pointer = component_cast<T*>(component);
				if(internal_pointer)
				{
					ComponentsManager::getSingleton()->reserveComponent(internal_pointer);
				}
			}
			
			virtual ~ComponentPtr()
			{
				ComponentsManager::getSingleton()->releaseComponent(internal_pointer);
			}
			
			T* operator->()
			{
				return internal_pointer;
			}
			
			operator bool()
			{
				if(internal_pointer) return true;
				return false;
			}
			
		private:
			T* internal_pointer;
			
		};
	}
}