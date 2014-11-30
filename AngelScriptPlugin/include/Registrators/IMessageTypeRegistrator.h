#pragma once

#include <Registrators/ITypeRegistrator.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class IMessageTypeRegistrator : public ITypeRegistrator
		{
		public:
			virtual bool registerSender(asIScriptEngine* script_engine) const = 0;
			virtual bool registerListener(asIScriptEngine* script_engine) const = 0;
		};
	}
}