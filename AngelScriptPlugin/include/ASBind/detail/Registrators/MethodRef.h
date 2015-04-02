#pragma once

#include <angelscript.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T, typename Retval, typename... Args>
		asSFuncPtr methodRef()(Retval (T::*f)(Args...))
		{
			asSFuncPtr ref = asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(Retval(T::*)(Args...))(f));
			return ref;
		}
	}
}
