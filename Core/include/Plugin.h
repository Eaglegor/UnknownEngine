#pragma once

/*
 * Plugin.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <string>

namespace UnknownEngine
{
	namespace Core
	{

		class PluginError: public std::exception
		{
			public:
				PluginError ( std::string plugin_name, std::string reason ) throw ()
				{
					reason = "Error loading plugin: " + plugin_name + "\n" +
							"Reported reason: " + reason;
				}

				const char* what () const throw () override
				{
					return reason.c_str();
				}
				~PluginError () throw ()
				{
				}
			private:
				std::string reason;
		};

		class Plugin
		{
			public:
				Plugin (){};
				virtual ~Plugin ();

				virtual bool install () throw (PluginError) = 0;

				virtual bool init () throw (PluginError) = 0;

				virtual bool shutdown () throw (PluginError) = 0;

				virtual bool uninstall () throw (PluginError) = 0;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
