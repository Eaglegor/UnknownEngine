#pragma once
/*
 * ComponentsManager.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>
#include <list>
#include <vector>

#include <ComponentSystem_export.h>
#include <Singleton.h>
#include <ComponentType.h>
#include <Exception.h>
#include <NumericIdentifierType.h>
#include <Dictionary.h>
#include <NoSuitableFactoryFoundException.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IComponentFactory;
		class Component;
		class ComponentDesc;
		class SubsystemDesc;
		class Entity;

		/**
		 * @brief Manager of components
		 *
		 * ####Concept
		 * Components manager is a proxy between subsystem's components factories and user code
		 * that wants to create components (loaders, other subsystems etc.).
		 * It creates entities which bind components together, receives requests for component's creation
		 * and delegates it to a concrete component factory registered by some subsystem.
		 *
		 * #### Usage
		 * When plugins manager loads a subsystem's plugin it calls Plugin::install() method.
		 * When this method is called the plugin creates factories for component types supported by this plugin.
		 * Then it calls ComponentsManager::addComponentFactory() for each of it's factories.
		 * Later if user code wants to create some simulation object it creates the entity
		 * by the call of ComponentsManager::createEntity() method. Then it must populate this entity with needed
		 * components - so it calls ComponentsManager::createComponent().
		 * Components manager tries to find a registered factory which is able to create a component
		 * of requested type. If such factory is found it's createComponent method is called.
		 * If no factory is found for requested component type, an exception is thrown.
		 *
		 */

		class ComponentsManager : public Singleton<ComponentsManager>
		{
			public:

				typedef Utils::Dictionary<NumericIdentifierType, std::string> InternalDictionaryType;
				typedef std::unordered_map<NumericIdentifierType, IComponentFactory*> ComponentFactoriesMap;

				/**
				 * @brief Default constructor. Called by Engine.
				 */
				COMPONENTSYSTEM_EXPORT
				ComponentsManager ();

				COMPONENTSYSTEM_EXPORT
				virtual ~ComponentsManager ();

				/**
				 * @brief Registers new component factory
				 * @param factory - Factory to register
				 *
				 * Note that the factory must have unique name, otherwise exception is thrown
				 *
				 */
				COMPONENTSYSTEM_EXPORT
				virtual void addComponentFactory ( IComponentFactory* factory );

				/**
				 * @brief Unregisters the component factory
				 * @param factory - Factory to unregister
				 *
				 */
				COMPONENTSYSTEM_EXPORT
				virtual void removeComponentFactory ( IComponentFactory* factory );

				/**
				 * @brief Creates the entity
				 * @param name - Entity name. Must be unique.
				 * @return Pointer to the newly created entity
				 */
				COMPONENTSYSTEM_EXPORT
				virtual Entity* createEntity ( const std::string &name );

				
				/**
				 * @brief Removes the entity
				 * @return Pointer to the entity to be removed
				 */
				COMPONENTSYSTEM_EXPORT
				virtual void removeEntity ( Entity* entity );


				/**
				 * @brief Creates the component
				 * @param desc - Component descriptor
				 * @return Pointer to the newly created component
				 */
				COMPONENTSYSTEM_EXPORT
				virtual Component* createComponent ( const ComponentDesc &desc, const Entity* parent_entity ) throw (NoSuitableFactoryFoundException);

				/**
				 * @brief Removes the component
				 * @param component - The component to be removed
				 */
				COMPONENTSYSTEM_EXPORT
				virtual void removeComponent( Component* component );

			private:
				ComponentFactoriesMap component_factories; ///< Map of registered component factories
				InternalDictionaryType internal_dictionary; ///< Internal dictionary implementation to assign identifiers to names

		};

#ifdef _MSC_VER
#ifndef ComponentSystem_EXPORTS
		extern template class COMPONENTSYSTEM_EXPORT Singleton<ComponentsManager>;
#else
		template class COMPONENTSYSTEM_EXPORT Singleton<ComponentsManager>;
#endif
#endif

	} /* namespace Core */
} /* namespace UnknownEngine */
