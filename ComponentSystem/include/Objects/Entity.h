#pragma once
/*
 * Entity.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <ComponentSystem_export.h>
#include <InlineSpecification.h>
#include <unordered_map>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		class Component;
		class ComponentsManager;

		/**
		 * @brief The single simulation object
		 *
		 * ####Summary
		 * Entity is considered as a single simulation object. The entity itself doesn't introduce any behavior.
		 * But it can have different behaviour aspects implemented in classes called \ref Component "components".
		 * Each component can live only inside it's entity. When the entity is destroyed, it's components are destroyed too.
		 *
		 * Each entity is identified by it's name which **must be unique**.
		 * If you try to create entity with already existing name an exception is thrown.
		 *
		 * ####Usage
		 * When user code wants to create a new game object (character, static background, trigger, ground plane etc.)
		 * it calls a ComponentsManager::createEntity() method. Then it must create some behavior aspects
		 * (rendering, physics, AI etc.). To do this it must create a \ref ComponentDescriptor "descriptor" for each
		 * behavior aspect and pass it to ComponentsManager::createComponent() method.
		 *
		 * Theoretically components can be created and removed dynamically at any time.
		 * But in practice it seems that components will be created at the beginning of entity's lifetime
		 * and removed at it's end. Lifetime of entity is not longer than components manager's lifetime so when
		 * components manager is terminated, all entities are terminated too.
		 * Entities can also be removed at any time by explicit calls to ComponentsManager::removeEntity().
		 *
		 */

		UNKNOWNENGINE_SIMPLE_EXCEPTION ( DuplicateComponentNameException );
		UNKNOWNENGINE_SIMPLE_EXCEPTION ( ComponentNotFoundException );

		class Entity
		{
			public:
				/**
				 * @brief Constructor
				 * @param name - **unique** name of game object
				 */
				COMPONENTSYSTEM_EXPORT
				Entity ( const std::string &name, ComponentsManager* components_manager );

				COMPONENTSYSTEM_EXPORT
				virtual ~Entity ();

				/**
				 * @brief Adds a component to the entity
				 * @param name - Local name of the component
				 * @param component - Component to add
				 */
				COMPONENTSYSTEM_EXPORT
				void addComponent ( const std::string &name, Component *component );

				/**
				 * @brief Removes the component from the entity
				 * @param name - Local name of component to remove
				 *
				 */
				COMPONENTSYSTEM_EXPORT
				void removeComponent ( const std::string &name );

				/**
				 * @brief Returns the entity name
				 * @return Entity name
				 */
				COMPONENTSYSTEM_EXPORT
				const std::string& getName();

				/**
				 * @brief Starts the entity's life
				 *
				 * This method must be called to notify entity that all it's components are created and can be started.
				 * The main purpose: minimize processing inside unfinished entities. The components if they depend on some other
				 * components must not start until the start method is called
				 *
				 */
				COMPONENTSYSTEM_EXPORT
				void start();

				/**
				  * @brief Returns the stored components map
				  */
				UNKNOWNENGINE_INLINE
				const std::unordered_map<std::string, Component*>& getComponents()
				{
					return components;
				}

			private:

				typedef std::unordered_map<std::string, Component*> InternalMapType;

				InternalMapType components; ///< Components map
				std::string name; ///< Entity name
				ComponentsManager* components_manager;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
