#pragma once

#include <Plugins_export.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PluginsManager;
		struct SubsystemDesc;

		class IPlugin
		{

			public:
				PLUGINS_EXPORT
				virtual ~IPlugin (){}

				PLUGINS_EXPORT
				virtual const char* getName() const = 0;

				PLUGINS_EXPORT
				virtual bool install (PluginsManager* plugins_manager, const SubsystemDesc &desc )  = 0;

				PLUGINS_EXPORT
				virtual bool init ()  = 0;

				PLUGINS_EXPORT
				virtual bool shutdown ()  = 0;

				PLUGINS_EXPORT
				virtual bool uninstall ()  = 0;
				
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
