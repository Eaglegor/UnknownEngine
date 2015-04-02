#pragma once

#include <ASBind/detail/Class.h>

namespace UnknownEngine
{
	namespace ASBind
	{

		template<typename T>
		struct RefCountingPolicy
		{
			virtual bool registerRefCounter(asIScriptEngine* script_engine, const std::string &object_name) const = 0;
			virtual ~RefCountingPolicy(){}
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

			static void stub(T* obj)
			{
			}
			
			bool registerRefCounter(asIScriptEngine* script_engine, const std::string &object_name) const
			{
				bool success = true;
				success = success && script_engine->RegisterObjectBehaviour(object_name.c_str(), asBEHAVE_ADDREF, "void f()", asFUNCTION(DontUseRefCounter<T>::stub), asCALL_CDECL_OBJFIRST);
				success = success && script_engine->RegisterObjectBehaviour(object_name.c_str(), asBEHAVE_RELEASE, "void f()", asFUNCTION(DontUseRefCounter<T>::stub), asCALL_CDECL_OBJFIRST);
				return success;
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
		class RefClass : public Class<T, RefClass<T>>
		{
			static_assert(std::is_base_of<RefCountingPolicy<T>, SelectedRefCountingPolicy>::value, "Reference counting policy expected as template parameter.");

			typedef Class<T, RefClass<T>> Base;
			public:
				RefClass(const std::string &name, Behavior::AngelScriptSubsystem *subsystem):
				Class<T, RefClass<T>>(name, subsystem, subsystem->getScriptEngine())
				{
					if(!subsystem->typeInfoIsBound<T>())
					{
						subsystem->bindTypeInfo<T>(name.c_str(), ClassType::REF_TYPE);
						subsystem->getScriptEngine()->RegisterObjectType(name.c_str(), 0, asOBJ_REF);
					}
				}

				RefClass& ref_counter(const SelectedRefCountingPolicy &policy = SelectedRefCountingPolicy())
				{
					policy.registerRefCounter(Base::engine, Base::name);
					return *this;
				}
				
				template<typename... Args>
				RefClass& constructor()
				{
					FactoryRegistrator<T, typename SelectedRefCountingPolicy::ActualObjectType>::template bindDefault<Args...>(Base::subsystem);
					return *this;
				}

		};
	}
}
