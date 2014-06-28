#pragma once

/*
 * DirectX10RenderSystemPlugin.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <Properties/Properties.h>
#include <Plugins/PluginExport.h>
#include <Plugins/Plugin.h>
#include <InlineSpecification.h>
#include <SubsystemDesc.h>
#include <ConsoleLogger.h>

namespace UnknownEngine
{

	namespace Core
	{
		class SubsystemDesc;
		class MessageDispatcher;
		class MessageDictionary;
		class ComponentsManager;
	}

	namespace Logger
	{

		class ConsoleLoggerPlugin: public Core::Plugin
		{
			public:
				ConsoleLoggerPlugin();
				virtual ~ConsoleLoggerPlugin();

				constexpr static const char* getNameConst()
				{
					return "Console logger";
				}

				UNKNOWNENGINE_INLINE
				virtual const char* getName() const override
				{
					return getNameConst();
				}

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc) throw (Core::PluginError) override;
				virtual bool init() throw (Core::PluginError) override;
				virtual bool shutdown() throw (Core::PluginError) override;
				virtual bool uninstall() throw (Core::PluginError) override;

			private:
				Core::SubsystemDesc desc;
				Core::ComponentsManager* components_manager;
				Core::MessageDispatcher* message_dispatcher;
				Core::MessageDictionary* message_dictionary;
				ConsoleLogger console_logger;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
