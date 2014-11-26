#pragma once

#include <Registrators/ITypeRegistrator.h>

#include <scriptstdstring.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class StdStringRegistrator : public ITypeRegistrator
		{
		public:
			virtual bool registerType ( asIScriptEngine* script_engine ) const override
			{
				RegisterStdString(script_engine);
				return true;
			}
		};
	}
}