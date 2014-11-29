#pragma once

#define ANGELSCRIPT_DLL_LIBRARY_IMPORT
#include <angelscript.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ITypeRegistrator
		{
		public:
			virtual bool registerType(asIScriptEngine* script_engine) const = 0;
			virtual const char* getRegisteredName() const = 0;
			virtual ~ITypeRegistrator(){};
		};
	}
}