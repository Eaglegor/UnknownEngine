#pragma once

#include <Plugins_export.h>
#include <list>
#include <Plugins/PluginError.h>
#include <Singleton.h>

namespace UnknownEngine
{

	namespace Core
	{

		class ILogger;

		class Plugin;
		struct SubsystemDesc;
		class EngineContext;

		class PluginsManager : public Singleton<PluginsManager, EngineContext*>
		{
			public:
				PLUGINS_EXPORT
				PluginsManager (EngineContext* engine_context);

				PLUGINS_EXPORT
				virtual ~PluginsManager ();

				PLUGINS_EXPORT
				void loadSubsystem ( const SubsystemDesc &desc );

				PLUGINS_EXPORT
				void initSubsystems();

				PLUGINS_EXPORT
				EngineContext* getEngineContext() const;

			private:
				void loadModule(const std::string &library_name, const SubsystemDesc &desc) ;

				EngineContext* engine_context;
				std::list<Plugin*> plugins;
				std::list<void*> libraries_handlers;
				ILogger* logger;
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
