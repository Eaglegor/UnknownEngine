#pragma once

#include <angelscript.h>
#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>
#include <ASBind/detail/RefCountingWrapper.h>
#include <iostream>

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
					std::cout << "Registering type: " << name << std::endl;
					if(!subsystem->typeNameIsBound<T>())
					{
						subsystem->bindTypeName<T>(name.c_str());
						engine->RegisterObjectType(name.c_str(), 0, asOBJ_REF);
					}
				}

				template<typename Retval, typename... Args>
				RefClass& method(Retval (T::*f)(Args...), const std::string &name)
				{
						std::cout << "Binding method: " + format_member_signature(f, name, subsystem) << std::endl;
						engine->RegisterObjectMethod(this->name.c_str(), format_member_signature(f, name, subsystem).c_str(), asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(Retval (T::*)(Args...))(f)), asCALL_THISCALL);
						return *this;
				}

				template<typename Retval, typename... Args>
				RefClass& static_method(Retval (T::*f)(Args...), const std::string &name)
				{
						engine->RegisterGlobalFunction(format_member_signature(f, name, subsystem).c_str(), asFUNCTION(f), asCALL_CDECL);
				}

				template<typename... Args>
				RefClass& constructor()
				{
					engine->RegisterObjectBehaviour(name, asBEHAVE_FACTORY, name + "@ f(" + FormattedArgumentsString<Args...>()() + ")", asFUNCTION(RefClass<T>::factoryFunc), asCALL_CDECL);
					registerRefCounter();
					return *this;
				}
				
				RefClass& default_constructor()
				{
					std::cout << "Binding constructor" << std::endl;
					engine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_FACTORY, (name + "@ f()").c_str(), asFUNCTION(RefClass<T>::defaultFactoryFunc), asCALL_CDECL);
					registerRefCounter();
					return *this;
				}

		private:
				template<typename... Args>
				static RefCountingWrapper<T>* factoryFunc(Args&& ...args)
				{
						return new RefCountingWrapper<T>(std::forward<Args>(args)...);
				}

				static RefCountingWrapper<T>* defaultFactoryFunc()
				{
					return new RefCountingWrapper<T>();
				}
				
				void registerRefCounter()
				{
					static bool ref_counter_is_bound = false;
					if(!ref_counter_is_bound)
					{
						engine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_ADDREF, "void f()", asMETHOD(RefCountingWrapper<T>, addRef), asCALL_THISCALL);
						engine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_RELEASE, "void f()", asMETHOD(RefCountingWrapper<T>, release), asCALL_THISCALL);
						ref_counter_is_bound = true;
					}
				}
				
				std::string name;
				Behavior::AngelScriptSubsystem* subsystem;
				asIScriptEngine* engine;

		};
	}
}
