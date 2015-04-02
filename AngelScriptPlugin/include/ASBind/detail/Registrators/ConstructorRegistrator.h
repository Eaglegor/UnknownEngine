#pragma once

#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class ConstructorRegistrator
		{
		public:
			template<typename... Args>
			static bool bindConstructor(void (*f)(void*, Args...), Behavior::AngelScriptSubsystem* subsystem)
			{
				return 0 <= subsystem->getScriptEngine()->RegisterObjectBehaviour ( FormattedTypeName<T>()(subsystem).c_str(), asBEHAVE_CONSTRUCT, format_signature<void, Args...>("f", subsystem).c_str(), asFUNCTION (f), asCALL_CDECL_OBJFIRST );
			}
			
			static bool bindDestructor(void (*f)(void*), Behavior::AngelScriptSubsystem* subsystem)
			{
				return 0 <= subsystem->getScriptEngine()->RegisterObjectBehaviour ( FormattedTypeName<T>()(subsystem).c_str(), asBEHAVE_DESTRUCT, format_signature<void>("f", subsystem).c_str(), asFUNCTION (f), asCALL_CDECL_OBJFIRST );
			}
			
			template<typename... Args>
			static void defaultConstructor(void *memory, Args&& ...args)
			{
				new(memory) T(std::forward<Args>(args)...);
			}
			
			static void defaultDestructor(void *memory)
			{
				static_cast<T*>(memory)->~T();
			}
			
			template<typename... Args>
			static bool bindDefaultConstructor(Behavior::AngelScriptSubsystem* subsystem)
			{
				return bindConstructor(&ConstructorRegistrator<T>::defaultConstructor<Args...>, subsystem);
			}
			
			static bool bindDefaultDestructor(Behavior::AngelScriptSubsystem* subsystem)
			{
				return bindDestructor(&ConstructorRegistrator<T>::defaultDestructor, subsystem);
			}
		};
	}
}