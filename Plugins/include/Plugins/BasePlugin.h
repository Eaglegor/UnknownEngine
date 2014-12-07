#pragma once

#include <Plugins/IPlugin.h>
#include <InlineSpecification.h>
#include <string>

namespace UnknownEngine
{
	namespace Core
	{

		class PluginsManager;
		struct SubsystemDesc;

		class BasePlugin : public IPlugin
		{

			public:
				BasePlugin(const char* name);

				UNKNOWNENGINE_INLINE
				virtual const char* getName() const override
				{
					return name.c_str();
				}
				
				virtual bool install (PluginsManager* plugins_manager, const SubsystemDesc &desc )  = 0;

				virtual bool init ()  = 0;

				virtual bool shutdown ()  = 0;

				virtual bool uninstall ()  = 0;

			private:
				const std::string name;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
