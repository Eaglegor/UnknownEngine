#pragma once

#include <ComponentType.h>

namespace UnknownEngine
{
	namespace Core
	{
		template <typename ObjectType, typename ObjectTypeId, typename DescriptorClass>
		class AbstractObjectFactory;
		
		class IComponent;
		struct ComponentDesc;
	
		typedef AbstractObjectFactory<IComponent, ComponentType, ComponentDesc> IComponentFactory;
	}
}