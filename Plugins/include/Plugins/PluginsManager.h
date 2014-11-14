#pragma once

/*
 * PluginsManager.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <Plugins_export.h>
#include <list>
#include <Plugins/PluginError.h>
#include <Singleton.h>

namespace UnknownEngine
{

	namespace Core
	{

		class Plugin;
		struct SubsystemDesc;
		class EngineContext;

		/**
		 * @brief Core subsystem responsible for loading/unloading plugins
		 */
		class PluginsManager : public Singleton<PluginsManager, EngineContext*>
		{
			public:
				/**
				 * @brief Constructor
				 * @param engine_context - %Engine context
				 */
				PLUGINS_EXPORT
				PluginsManager (EngineContext* engine_context);

				PLUGINS_EXPORT
				virtual ~PluginsManager ();

				/**
				 * @brief Loads plugin by descriptor passed
				 * @param desc - Descriptor of subsystems to be loaded
				 */
				PLUGINS_EXPORT
				void loadSubsystem ( const SubsystemDesc &desc );

				/**
				 * @brief Initializes all subsystems
				 */
				PLUGINS_EXPORT
				void initSubsystems();

				/**
				 * @brief Returns the engine context.
				 * @return %Engine context
				 */
				PLUGINS_EXPORT
				EngineContext* getEngineContext() const;

			private:
				/**
				 * @brief Loads the specified shared library
				 * @param library_name - Shared library name
				 * @param desc - Subsystem descriptor
				 */
				void loadModule(const std::string &library_name, const SubsystemDesc &desc) ;

				EngineContext* engine_context; ///< %Engine context
				std::list<Plugin*> plugins; ///< List of loaded plugins
				std::list<void*> libraries_handlers; ///< List of loaded libraries handlers
		};

#ifdef _MSC_VER
#ifndef Plugins_EXPORTS
		extern template class PLUGINS_EXPORT Singleton<PluginsManager, EngineContext*>;
#else
		template class PLUGINS_EXPORT Singleton<PluginsManager, EngineContext*>;
#endif
#endif

	} /* namespace Core */
} /* namespace UnknownEngine */
