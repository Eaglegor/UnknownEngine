#pragma once

#include <AngelScriptSubsystem.h>
#include <ASBind/detail/FormatSignature.h>
#include <ASBind/detail/Registrators/MethodRef.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class UnaryMinusOperatorRegistrator
		{
		public:
			static bool bind(T (*opr)(T*), Behavior::AngelScriptSubsystem* subsystem)
			{
				return subsystem->getScriptEngine()->RegisterObjectMethod(FormattedTypeName<T>()().c_str(), format_signature(opr, "opNeg", subsystem).c_str(), getDefaultSignature().c_str(), asFUNCTION(opr), asCALL_CDECL_OBJLAST);
			}

			static bool bind(T (T::*opr), Behavior::AngelScriptSubsystem* subsystem)
			{
				return subsystem->getScriptEngine()->RegisterObjectMethod(FormattedTypeName<T>()().c_str(), format_member_signature(opr, "opNeg", subsystem).c_str(), methodRef(opr), asCALL_THISCALL);
			}

			static T defaultUnaryMinusOperator(T* t)
			{
				return -(*t);
			}

			static bool bindDefault(Behavior::AngelScriptSubsystem* subsystem)
			{
				return bind(&UnaryMinusOperatorRegistrator<T>::defaultUnaryMinusOperator, subsystem);
			}
		};
	}
}
