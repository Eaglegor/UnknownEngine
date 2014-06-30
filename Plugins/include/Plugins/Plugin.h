#pragma once

/*
 * Plugin.h
 *
 *  Created on: 16 июня 2014 г.
 *      Author: Eaglegor
 */

#include <Plugins/PluginError.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PluginsManager;
		class SubsystemDesc;

		class Plugin
		{

			public:
				Plugin (){}
				virtual ~Plugin (){}

				virtual const char* getName() const = 0;

				virtual bool install (PluginsManager* plugins_manager, const SubsystemDesc &desc ) throw (PluginError) = 0;

				virtual bool init () throw (PluginError) = 0;

				virtual bool shutdown () throw (PluginError) = 0;

				virtual bool uninstall () throw (PluginError) = 0;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
