#pragma once

#include <Registrators/ITypeRegistrator.h>
#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		template <typename T>
		class ClassValueTypeRegistrator : public ITypeRegistrator
		{
		public:
			
			ClassValueTypeRegistrator(const std::string& registered_name, const std::string& declaration_namespace = ""):
			registered_name(registered_name),
			declaration_namespace(declaration_namespace),
			full_name(declaration_namespace.empty() ? registered_name : declaration_namespace + "::" + registered_name)
			{}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const override
			{
				script_engine->SetDefaultNamespace(declaration_namespace.c_str());
				
				bool success = registerTypeImpl(script_engine);
				
				script_engine->SetDefaultNamespace("");
				
				return success;
			}

			virtual const char* getRegisteredName() const override
			{
				return registered_name.c_str();
			}
			
			virtual const char* getRegisteredNameWithNamespace() const override
			{
				return full_name.c_str();
			}
			
		protected:
			virtual bool registerConstructor( asIScriptEngine* script_engine ) const
			{
				int result = script_engine->RegisterObjectBehaviour(registered_name.c_str(), asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ClassValueTypeRegistrator<T>::defaultConstructor), asCALL_CDECL_OBJLAST);
				return result >= 0;
			}
			
			virtual bool registerDestructor( asIScriptEngine* script_engine ) const
			{
				int result = script_engine->RegisterObjectBehaviour(registered_name.c_str(), asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ClassValueTypeRegistrator<T>::defaultDestructor), asCALL_CDECL_OBJLAST);
				return result >= 0;
			}			
			
			virtual bool registerProperties( asIScriptEngine* script_engine ) const
			{
				return true;
			}
			
			virtual bool registerMethods( asIScriptEngine* script_engine ) const
			{
				 return true;
			}
			
			virtual bool registerRelatedTypes( asIScriptEngine* script_engine) const
			{
				return true;
			}
			
		private:
			static void defaultConstructor(void *memory)
			{
				new(memory) T();
			}
			
			static void defaultDestructor(void *memory)
			{
				static_cast<T*>(memory)->~T();
			}

			bool registerTypeImpl ( asIScriptEngine* script_engine ) const
			{
#if AS_CAN_USE_CPP11
				asUINT traits_flag = asGetTypeTraits<T>();
#else
				asUINT traits_flag = 0;
#endif
				int result = script_engine->RegisterObjectType(registered_name.c_str(), sizeof(T), asOBJ_VALUE | traits_flag);
				if(result < 0) return false;
				if(registerConstructor(script_engine) && registerDestructor(script_engine))
				{
					return registerProperties(script_engine) && registerMethods(script_engine) && registerRelatedTypes(script_engine);
				}
				return false;
			}
			
			const std::string registered_name;
			const std::string declaration_namespace;
			const std::string full_name;
			
		};
	}
}