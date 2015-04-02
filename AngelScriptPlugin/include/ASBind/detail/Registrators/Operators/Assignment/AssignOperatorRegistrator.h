#pragma once

#include <ASBind/detail/FormatSignature.h>
#include <ASBind/detail/Registrators/MethodRef.h>
#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class AssignOperatorRegistrator
		{
			public:
				static bool bind(T& (*opr)(T*, const T&), Behavior::AngelScriptSubsystem *subsystem)
				{
					return  0 <= subsystem->getScriptEngine()->RegisterObjectMethod(FormattedTypeName<T>()(subsystem).c_str(), format_signature<T*, const T&>("opAssign", subsystem).c_str(), asFUNCTION(opr), asCALL_CDECL_OBJFIRST);
				}

				static bool bind(T& (T::*opr)(const T&), Behavior::AngelScriptSubsystem *subsystem)
				{
					return  0 <= subsystem->getScriptEngine()->RegisterObjectMethod(FormattedTypeName<T>()(subsystem).c_str(), format_member_signature(opr, "opAssign", subsystem).c_str(), methodRef(opr), asCALL_THISCALL);
				}

				static T& defaultAssignmentOperator(T* obj, const T& rhs)
				{
					*obj = rhs;
					return *obj;
				}
				
				static bool bindDefault(Behavior::AngelScriptSubsystem *subsystem)
				{
					return bind(&AssignOperatorRegistrator<T>::defaultAssignmentOperator, subsystem);
				}
		};
	}
}
