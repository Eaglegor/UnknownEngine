#pragma once

#include <angelscript.h>
#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>
#include <ASBind/detail/RefCountingWrapper.h>
#include <iostream>
#include <ASBind/Namespace.h>
#include <ASBind/detail/Registrators/MethodRegistrator.h>

namespace UnknownEngine
{
	namespace ASBind
	{

		template<typename T>
		struct RefCountingPolicy
		{
			virtual bool registerRefCounter(asIScriptEngine* script_engine, const std::string &object_name) const = 0;
		};

		template<typename T>
		struct UseAutoRefCounter : public RefCountingPolicy<T>
		{
			typedef RefCountingWrapper<T> ActualObjectType;

			bool registerRefCounter(asIScriptEngine* script_engine, const std::string &object_name) const
			{
				bool success = true;
				success = success && script_engine->RegisterObjectBehaviour(object_name.c_str(), asBEHAVE_ADDREF, "void f()", asMETHOD(RefCountingWrapper<T>, addRef), asCALL_THISCALL);
				success = success && script_engine->RegisterObjectBehaviour(object_name.c_str(), asBEHAVE_RELEASE, "void f()", asMETHOD(RefCountingWrapper<T>, release), asCALL_THISCALL);
				return success;
			}
		};

		template<typename T>
		struct DontUseRefCounter : public RefCountingPolicy<T>
		{
			typedef T ActualObjectType;

				bool registerRefCounter(asIScriptEngine* script_engine, const std::string &object_name) const
				{
					return true;
				}
		};

		template<typename T, typename ReturnedObjectType = T>
		struct UseCustomRefCounter : public RefCountingPolicy<T>
		{
			typedef ReturnedObjectType ActualObjectType;

			UseCustomRefCounter( void (ReturnedObjectType::*addref)(), void (ReturnedObjectType::*release)()):
			addref_func(addref),
			release_func(release)
			{
			}

			bool registerRefCounter(asIScriptEngine* script_engine, const std::string &object_name) const
			{
				bool success = true;
				success = success && script_engine->RegisterObjectBehaviour(object_name.c_str(), asBEHAVE_ADDREF, "void f()", asSMethodPtr<sizeof(void (ReturnedObjectType::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(void (ReturnedObjectType::*)())(addref_func)), asCALL_THISCALL);
				success = success && script_engine->RegisterObjectBehaviour(object_name.c_str(), asBEHAVE_RELEASE, "void f()", asSMethodPtr<sizeof(void (ReturnedObjectType::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(void (ReturnedObjectType::*)())(release_func)), asCALL_THISCALL);
				return  success;
			}

			private:
			void (ReturnedObjectType::*addref_func)();
			void (ReturnedObjectType::*release_func)();
		};

		template<typename T, typename SelectedRefCountingPolicy = UseAutoRefCounter<T>>
		class RefClass
		{
			static_assert(std::is_base_of<RefCountingPolicy<T>, SelectedRefCountingPolicy>::value, "Reference counting policy expected as template parameter.");

			public:
				RefClass(const std::string &name, Behavior::AngelScriptSubsystem *subsystem):
				name(name),
				subsystem(subsystem),
				engine(subsystem->getScriptEngine())
				{
					std::cout << "Registering type: " << name << std::endl;
					if(!subsystem->typeNameIsBound<T>())
					{
						subsystem->bindTypeInfo<T>(name.c_str(), ClassType::REF_TYPE);
						engine->RegisterObjectType(name.c_str(), 0, asOBJ_REF);
					}
				}

				RefClass& ref_counter(const SelectedRefCountingPolicy &policy = SelectedRefCountingPolicy())
				{
					policy.registerRefCounter(engine, name);
				}

				template<typename Retval, typename... Args>
				RefClass& method(Retval (T::*f)(Args...), const std::string &name)
				{
					MethodRegistrator<T>::bind_non_static(f, name.c_str(), subsystem);
					return *this;
				}

				template<typename Retval, typename... Args>
				RefClass& static_method(Retval (T::*f)(Args...), const std::string &name)
				{
					MethodRegistrator<T>::bind_static(f, name.c_str(), subsystem);
					return *this;
				}

				template<typename... Args>
				RefClass& constructor()
				{
					engine->RegisterObjectBehaviour(name, asBEHAVE_FACTORY, name + "@ f(" + FormattedArgumentsString<Args...>()() + ")", asFUNCTION(RefClass<T>::factoryFunc), asCALL_CDECL);
					return *this;
				}
				
				RefClass& default_constructor()
				{
					engine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_FACTORY, (name + "@ f()").c_str(), asFUNCTION(RefClass<T>::defaultFactoryFunc), asCALL_CDECL);
					return *this;
				}

		private:
				template<typename... Args>
				static SelectedRefCountingPolicy::ActualObjectType* factoryFunc(Args&& ...args)
				{
					return new SelectedRefCountingPolicy::ActualObjectType(std::forward<Args>(args)...);
				}

				static SelectedRefCountingPolicy::ActualObjectType* defaultFactoryFunc()
				{
					return new SelectedRefCountingPolicy::ActualObjectType();
				}

				std::string name;
				Behavior::AngelScriptSubsystem* subsystem;
				asIScriptEngine* engine;

		};
	}
}
