#pragma once

#include <AngelScript.h>
#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>
#include <new>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class ValueClass
		{
			public:
				ValueClass(const std::string &name, Behavior::AngelScriptSubsystem *subsystem):
				name(name),
				subsystem(subsystem),
				engine(subsystem->getScriptEngine())
				{
					if(!subsystem->typeNameIsBound<T>())
					{
						subsystem->bindTypeName<T>(name);
						engine->RegisterObjectType(name.c_str(), sizeof(T), asOBJ_VALUE);
					}
					else
					{
						// LOG_ERROR - type already bound
					}
				}

				template<typename Retval, typename... Args>
				ValueClass& method(Retval (T::*f)(Args...), const std::string &name)
				{
						engine->RegisterObjectMethod(name, format_signature<Retval, Args...>(), asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(Retval (T::*)(Args...))(f)), asCALL_THISCALL);
						return *this;
				}

				template<typename Retval, typename... Args>
				ValueClass& static_method(Retval (T::*f)(Args...), const std::string &name)
				{
						engine->RegisterGlobalFunction(format_signature(f), asFUNCTION(f), asCALL_CDECL);
				}

				template<typename... Args>
				ValueClass& constructor()
				{
						engine->RegisterObjectBehaviour(name, asBEHAVE_CONSTRUCT, "void f(" + FormattedArgumentsString<Args...>()() + ")", asFUNCTION(ValueClass::constructor), asCALL_CDECL_OBJLAST);
				}

				ValueClass& destructor()
				{
					engine->RegisterObjectBehaviour(name, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueClass::destructor), asCALL_CDECL_OBJLAST);
				}

		private:
				template<typename... Args>
				static void constructor(void* memory, Args&& ...args)
				{
					new(memory) T(std::forward<Args>(args)...);
				}

				static void destructor(void* memory)
				{
					static_cast<T*>(memory)->~T();
				}

				std::string name;
				Behavior::AngelScriptSubsystem* subsystem;
				asIScriptEngine* engine;

		};
	}
}
