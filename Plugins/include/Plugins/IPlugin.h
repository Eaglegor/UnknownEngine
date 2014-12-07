#pragma once

namespace UnknownEngine
{
	namespace Core
	{

		class PluginsManager;
		struct SubsystemDesc;

		class IPlugin
		{

			public:
				virtual ~IPlugin (){}

				virtual const char* getName() const = 0;

				virtual bool install (PluginsManager* plugins_manager, const SubsystemDesc &desc )  = 0;

				virtual bool init ()  = 0;

				virtual bool shutdown ()  = 0;

				virtual bool uninstall ()  = 0;
				
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
