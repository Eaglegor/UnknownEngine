#pragma once

/*
 * PluginError.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		/// Is thrown if plugin initialization failed
		UNKNOWNENGINE_SIMPLE_EXCEPTION(PluginError);

	}
}
