#pragma once

#include <ComponentType.h>

namespace UnknownEngine
{
	namespace Core
	{
		template <typename ObjectType, typename ObjectTypeId, typename DescriptorClass>
		class BaseObjectFactory;
		
		class IComponent;
		class ComponentDesc;
		
		typedef BaseObjectFactory<IComponent, ComponentType, ComponentDesc> BaseComponentFactory;
	}
}