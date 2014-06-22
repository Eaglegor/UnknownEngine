#pragma once

/*
 * Plugin.h
 *
 *  Created on: 16 ���� 2014 �.
 *      Author: Eaglegor
 */

#include <string>
#include <Plugins/PluginError.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PluginsManager;

		class Plugin
		{

			public:
				Plugin (){}
				virtual ~Plugin (){}

				virtual const char* getName() const = 0;

				virtual bool install (PluginsManager* plugins_manager) throw (PluginError) = 0;

				virtual bool init () throw (PluginError) = 0;

				virtual bool shutdown () throw (PluginError) = 0;

				virtual bool uninstall () throw (PluginError) = 0;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
