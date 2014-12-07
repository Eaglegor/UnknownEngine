#pragma once

#include <Plugins_export.h>
#include <list>
#include <Singleton.h>
#include <LogHelper.h>

namespace UnknownEngine
{

	namespace Core
	{

		class ILogger;

		class IPlugin;
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
				bool loadSubsystem ( const SubsystemDesc &desc );

				PLUGINS_EXPORT
				void initSubsystems();

				PLUGINS_EXPORT
				EngineContext* getEngineContext() const;

			private:
				bool loadModule(const char* library_name, const SubsystemDesc &desc) ;

				EngineContext* engine_context;
				std::list<IPlugin*> plugins;
				std::list<void*> libraries_handlers;
				LogHelper logger;
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
