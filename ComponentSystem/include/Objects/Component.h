#pragma once
/*
 * Component.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */
#include <ComponentSystem_export.h>
#include <ComponentType.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		*  @brief A behavior part of simulation object
		*
		* 	### Concept
		*	%Component is one of the main concepts of Unknown %Engine.
		*	It is a single portion of simulation object's behavior. This behavior may be rendering, physics, AI, logging or any other logic.
		*
		*	### Usage
		*	When some behavior aspect is needed for a simulation object, the appropriate component must be created and added to the Entity.
		*	The behavior itself is implemented in some loadable subsystem (plugin). This subsystem registers a factory which is able to
		*	create a component of specified type at \ref Docs_ComponentSystem_ComponentsManager "Components manager" which then creates a
		*	component and adds it to the entity.
		*
		*	A component may be a simple wrapper over subsystem's internal object (e.g. if we implement the adapter for some external subsystem
		*	(rendering, physics) or directly implement some logic (logging, scripting).
		*
		*	The components can't access each other directly. **There is no way to directly ask for a component/entity/subsystem from any
		*	other component/entity/subsystem**.
		*	The only legal way of communication between subsystems and components is to use \ref Docs_ComponentSystem_Message "messages".
		*
		*	#### Example
		*
		*	Let's suppose we have 3 components: *Graphics*, *Physics*, *Logic*. We want to draw a yellow physical sphere object
		*	and want to change it's color to red when it reaches some area. For simplicity we have no multithreading.
		*
		*	Every frame all listeners receive a message of type *UpdateFrameMessage*. When the physics subsystem receives such message,
		*	it internally updates it's components (we are interested in transform's update). And when it's done our *Physics*
		*	component sends a message *TransformChangedMessage*.
		*
		*	*Graphics* and *Logic* subscribe to this message and when it's received, they do their part of work.
		*
		*	*Graphics* component updates it's internal data structures (matrices, quaternions, vectors, transforms - depends on renderer's implementation).
		*
		*	*Logic* component checks if sphere's transform is in requested area and if this condition is met it sends a message
		*	like *ChangeMaterialActionMessage* exported by loaded graphics subsystem.
		*
		*	*Graphics* component subscribes to this message type and when it's received changes the color.
		*
		*	> *Note that such ChangeMaterialActionMessage is not a built-in message for the engine. Engine doesn't know anything about
		*	> such feature of rendering system as changing material. This message type is registered by graphics subsystem at loading
		*	> time and is avaiable for other subsystems through graphics subsystem's include files.*
		*	>
		*	> So logic subsystem includes something like: `<ExportedMessages/ChangeMaterialActionMessage.h>` and can then create and
		*	> send message of such type using \ref Docs_ComponentSystem_MessageDispatcher message dispatcher.
		*
		*	When graphics subsystem receives an *UpdateFrameMessage* it draws the object according to current *Graphics* component's state.
		*
		*	Logic subsystem when received *UpdateFrameMessage* just does nothing because it's purely event-based and doesn't need any frame synchronization.
		*
		*/

		class Entity;

		class Component
		{
			public:
				explicit Component ( const std::string &name )
					: name ( name ) {}

				/**
				 * @brief Is called when the component is created
				 *
				 * The init stuff must be done in this method. Is called by parent entity after component addition.
				 *
				 */
				virtual void init ( const Entity* parent_entity ) = 0;

				/**
				 *  @brief Is called when the parent entity is started
				 *
				 *  At this moment it's known that all components of the entity are created.
				 * 
				 *  @deprecated I think, there is no need for such a method because we don't exactly want
				 *  to have all components start their life simultaneously. We may want to add/delete components during
				 *  the entity's lifetime.
				 *
				 */
				virtual void start(){};

				/**
				 *  @brief Is called when the parent entity is about to be destroyed
				 *
				 * Stop any logic there. Prepare to destruction;
				 * Is called by entity.
				 *
				 */
				virtual void shutdown() = 0;

				/**
				 * @brief Returns the type of component
				 * @return Type of component
				 */
				virtual ComponentType getType() = 0;

				UNKNOWNENGINE_INLINE
				std::string getName()
				{
					return name;
				}

				virtual ~Component () {};

			private:
				std::string name;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
