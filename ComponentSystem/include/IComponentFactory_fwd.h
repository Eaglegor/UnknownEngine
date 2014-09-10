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
		
		/**
		 * @brief Factory to create components
		 *
		 * #### Concept
		 * Component factory is provided by some subsystems to create components.
		 * All component factories must implement the interface IComponentFactory.
		 *
		 * Note that this interface is a result of instantiating a templated factory interface AbstractObjectFactory.
		 *
		 * #### Usage
		 *
		 * When the plugin is loaded, it registers some component factories at components manager.
		 * When components manager is told to create a component it delegates the actual creation to
		 * the suitable factory. Factory gets a descriptor, creates the component and returns pointer to it.
		 *
		 * When the components manager is told to destroy a component it also delegates this work to
		 * factory because a components manager itself doesn't know how exactly the object was created - created
		 * with *new*, or created with some allocator, or just taken from the objects pool.
		 * But the factory knows it. That's why recycling of objects is delegated to factories which have created them.
		 *
		 * To choose appropriate factory to delegate component's creation components manager uses the
		 * \ref ComponentType "type identifier" of component.
		 * Some factories may create only one object, some may create different objects. All registered
		 * factories must have a **unique** name.
		 *
		 */
				
		typedef AbstractObjectFactory<IComponent, ComponentType, ComponentDesc> IComponentFactory;
	}
}