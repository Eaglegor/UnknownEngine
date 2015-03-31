#pragma once

#include <AngelScript.h>
#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class RefClass
		{
			public:
				RefClass(const std::string &name, Behavior::AngelScriptSubsystem *subsystem):
				name(name),
				subsystem(subsystem),
				engine(subsystem->getScriptEngine())
				{
					if(!subsystem->typeNameIsBound<T>())
					{
						subsystem->bindTypeName<T>(name);
						engine->RegisterObjectType(name.c_str(), 0, asOBJ_REF);
					}
					else
					{
						// LOG_ERROR - type already bound
					}
				}

				template<typename Retval, typename... Args>
				RefClass& method(Retval (T::*f)(Args...), const std::string &name)
				{
						engine->RegisterObjectMethod(name, format_signature<Retval, Args...>(), asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(Retval (T::*)(Args...))(f)), asCALL_THISCALL);
						return *this;
				}

				template<typename Retval, typename... Args>
				RefClass& static_method(Retval (T::*f)(Args...), const std::string &name)
				{
						engine->RegisterGlobalFunction(format_signature(f), asFUNCTION(f), asCALL_CDECL);
				}

				template<typename... Args>
				RefClass& constructor()
				{
						engine->RegisterObjectBehaviour(name, asBEHAVE_FACTORY, name + "@ f(" + FormattedArgumentsString<Args...>()() + ")", asFUNCTION(ASClass<T>::defaultFactoryFunc), asCALL_CDECL);
				}

				RefClass& defaultRefcounter()
				{
						engine->RegisterObjectBehaviour(name, asBEHAVE_ADDREF, "void f()", asFUNCTION(ASClass<T>::addRef), asCALL_CDECL_OBJFIRST);
						engine->RegisterObjectBehaviour(name, asBEHAVE_RELEASE, "void f()", asFUNCTION(ASClass<T>::release), asCALL_CDECL_OBJFIRST);
				}

				RefClass& customRefcounter( void (T::*add_ref_behavior)(), void (T::*release_behavior)() )
				{
						engine->RegisterObjectBehaviour(name, asBEHAVE_ADDREF, "void f()", asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(void (T::*)())(add_ref_behavior)), asCALL_THISCALL);
						engine->RegisterObjectBehaviour(name, asBEHAVE_RELEASE, "void f()", asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(void (T::*)())(release_behavior)), asCALL_THISCALL);
				}

				RefClass& static_customRefcounter(void (*add_ref_behavior) (T*), void (*release_behavior)(T*))
				{
						engine->RegisterObjectBehaviour(name, asBEHAVE_ADDREF, "void f()", asFUNCTION(add_ref_behavior), asCALL_CDECL_OBJFIRST);
						engine->RegisterObjectBehaviour(name, asBEHAVE_RELEASE, "void f()", asFUNCTION(release_behavior), asCALL_CDECL_OBJFIRST);
				}

		private:
				template<typename... Args>
				static T* defaultFactoryFunc(Args&& ...args)
				{
						return new T(std::forward<Args>(args)...);
				}

				static void addRef(T* obj)
				{
						// Call to subsystem addref
				}

				static void release(T* obj)
				{
						// Call to subsystem release
				}

				std::string name;
				Behavior::AngelScriptSubsystem* subsystem;
				asIScriptEngine* engine;

		};
	}
}
