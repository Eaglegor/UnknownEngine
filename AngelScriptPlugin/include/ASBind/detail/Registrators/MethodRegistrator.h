#pragma once

#include <ASBind/detail/FormatSignature.h>
#include <ASBind/Namespace.h>
#include <ASBind/detail/Registrators/MethodRef.h>

#include <AngelScriptSubsystem.h>

#include <LogHelper.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class MethodRegistrator
		{
		public:
			template<typename Retval, typename... Args>
			static bool bind_non_static(Retval (T::*f)(Args...), const char* method_name, Behavior::AngelScriptSubsystem* subsystem)
			{
				//Core::LogHelper logger("ASBind.MethodRegistrator", Core::LogSeverity::DEBUG);
				//LOG_DEBUG(logger, "Registering object method: " + FormattedTypeName<T>()(subsystem) + " ==> " + format_member_signature(f, method_name, subsystem));
				return 0 <= subsystem->getScriptEngine()->RegisterObjectMethod(FormattedTypeName<T>()(subsystem).c_str(), format_member_signature(f, method_name, subsystem).c_str(), methodRef(f), asCALL_THISCALL);
			}

			template<typename Retval, typename... Args>
			static bool bind_non_static(Retval (T::*f)(Args...), const char* method_name, Behavior::AngelScriptSubsystem* subsystem, const char* custom_signature)
			{
				return 0 <= subsystem->getScriptEngine()->RegisterObjectMethod(FormattedTypeName<T>()(subsystem).c_str(), custom_signature, methodRef(f), asCALL_THISCALL);
			}
			
			template<typename Retval, typename... Args>
			static bool bind_static(Retval (*f)(Args...), const char* method_name, Behavior::AngelScriptSubsystem* subsystem)
			{
				//Core::LogHelper logger("ASBind.MethodRegistrator", Core::LogSeverity::DEBUG);
				//LOG_DEBUG(logger, "Registering object method: " + FormattedTypeName<T>()(subsystem) + " ==> " + format_signature(f, method_name, subsystem));
				{
					Namespace(FormattedTypeName<T>()(subsystem), subsystem);
					return 0 <= subsystem->getScriptEngine()->RegisterGlobalFunction(format_signature(f, method_name, subsystem).c_str(), asFUNCTION(f), asCALL_CDECL);
				}
			}
			
			template<typename Retval, typename... Args>
			static bool bind_static(Retval (*f)(Args...), const char* method_name, Behavior::AngelScriptSubsystem* subsystem, const char* custom_signature)
			{
				{
					Namespace(FormattedTypeName<T>()(subsystem), subsystem);
					return 0 <= subsystem->getScriptEngine()->RegisterGlobalFunction(custom_signature, asFUNCTION(f), asCALL_CDECL);
				}
			}
		};
	}
}
