#pragma once

/*
 * Plugin.h
 *
 *  Created on: 16 июня 2014 г.
 *      Author: Eaglegor
 */

#include <Plugins/PluginError.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PluginsManager;
		struct SubsystemDesc;

		/**
		 * @brief Loadable subsystem
		 *
		 * ###Concept
		 * Unknown %Engine provides only basic playground to implement behavior.
		 * All concrete behaviours are implemented by loadable subsystems (rendering, physics, scripring etc.)
		 * Plugin is the main class of loadable subsystem. It provides interface to init and shutdown subsystem.
		 *
		 * ###Usage
		 * When you implement the new subsystem you have to do 2 things:
		 * - Create a class inherited from Plugin and implement it's lifecycle methods
		 * - Create C-style dll entry and exit points to create and remove the actual plugin class
		 *
		 */
		class Plugin
		{

			public:
				virtual ~Plugin (){}

				/**
				 * @brief Returns subsystem name
				 * @return Subsystem name
				 */
				UNKNOWNENGINE_INLINE
				std::string getName() const{ return name; }

				/**
				 * @brief Sets subsystem name
				 */
				UNKNOWNENGINE_INLINE
				void setName(const std::string& name) {this->name = name;}

				/**
				 * @brief Performs actions needed just after loading library
				 * @param plugins_manager - Plugins manager which created this plugin
				 * @param desc - Subsystem descriptor passed to the plugin
				 *
				 * At this moment plugin class is already created but there is no guarantee that all needed subsystems
				 * are already loaded. That's why this method must perform actions independent from other subsystems.
				 * Such actions could be:
				 * - saving plugin descriptor for future in some way
				 * - registering new message types at message dictionary
				 * - registering component factories
				 * - creating and initializing internal data structures
				 *
				 * You can't:
				 * - create message listeners (cause there may be still no corresponding message types registered)
				 * - create components (cause there may be still no corresponding factory registered)
				 *
				 * It's highly recommended to register new message types at this time because they may be
				 * needed by some other subsystems at the init stage.
				 *
				 * @return true if plugin successfully installed
				 */
				virtual bool install (PluginsManager* plugins_manager, const SubsystemDesc &desc )  = 0;

				/**
				 * @brief Performs actions needed to init plugin
				 *
				 * At this moment all subsystems are already installed. Not all of them are initialized.
				 * This method can perform any actions which don't require that other subsystems are initialized.
				 * Such actions could be:
				 * - same as during install
				 * - creating message listeners
				 *
				 * You can't:
				 * - create components (cause there may be still no corresponding factory registered)
				 *
				 * @return true if plugin init successfully
				 */
				virtual bool init ()  = 0;

				/**
				 * @brief Shuts down the plugin
				 *
				 * At this moment the engine is stopping it's work - so you must clear all non-persistent internal data
				 * at prepare to be unloaded. You need to do the init() work in reverse order:
				 * - unregister message listeners
				 *
				 * Note that you may be not uninstalled later. The user may want to just restart you calling init().
				 *
				 * @return true if shutdown successful
				 */
				virtual bool shutdown ()  = 0;

				/**
				 * @brief Uninstalls the plugin
				 *
				 * At this moment you are about to be unloaded. So you must do the install() work in reverse order:
				 * - delete internal data structures
				 * - unregister factories
				 * - unregister message types
				 *
				 * @return true if uninstalled successful
				 */
				virtual bool uninstall ()  = 0;

			private:
				std::string name; ///< Subsystem name

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
