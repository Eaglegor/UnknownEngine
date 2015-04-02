#pragma once


#include <ASBind/detail/FormatSignature.h>
#include <ASBind/Namespace.h>
#include <ASBind/detail/Registrators/MethodRef.h>

#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class MethodRegistrator
		{
		public:
			template<typename Retval, typename T, typename... Args>
			static bool bind_non_static(Retval (T::*f)(Args...), const char* method_name, Behavior::AngelScriptSubsystem* subsystem)
			{
				return subsystem->getScriptEngine()->RegisterObjectMethod(FormattedTypeName<T>()().c_str(), format_member_signature(f, method_name, subsystem).c_str(), methodRef(f), asCALL_THISCALL);
			}

			template<typename Retval, typename T, typename... Args>
			static bool bind_static(Retval (T::*f)(Args...), const char* method_name, Behavior::AngelScriptSubsystem* subsystem)
			{
				{
					Namespace(FormattedTypeName<T>()(), subsystem);
					return subsystem->getScriptEngine()->RegisterGlobalFunction(format_member_signature(f, method_name, subsystem).c_str(), asFUNCTION(f), asCALL_CDECL);
				}
			}
		};
	}
}
