#pragma once

/*
 * PluginError.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
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
					reason = "Error loading plugin: " + plugin_name + "\n" + "Reported reason: " + reason;
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
	}
}
