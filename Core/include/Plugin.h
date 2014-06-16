#pragma once

/*
 * Plugin.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <string>
#include <PluginError.h>

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

				virtual std::string getName() const = 0;

				virtual bool install (PluginsManager* plugins_manager) throw (PluginError) = 0;

				virtual bool init () throw (PluginError) = 0;

				virtual bool shutdown () throw (PluginError) = 0;

				virtual bool uninstall () throw (PluginError) = 0;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
