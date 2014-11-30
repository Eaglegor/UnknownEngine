#pragma once

#include <Registrators/ITypeRegistrator.h>
#include <Components/AngelScriptMessageListener.h>
#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		template<typename T>
		class MessageListenerRegistrator : public ITypeRegistrator
		{
		public:
			MessageListenerRegistrator(const std::string &message_type_name):
			registered_type_name("MessageListener<" + message_type_name +">"),
			message_type_name(message_type_name)
			{
			}
			
			virtual const char* getRegisteredName() const override
			{
				return registered_type_name.c_str();
			}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const override
			{
				
				script_engine->SetDefaultNamespace("Core");
				
				bool success = registerTypeImpl(script_engine);
				
				script_engine->SetDefaultNamespace("");
				
				return success;
			}

		private:
			
			bool registerTypeImpl ( asIScriptEngine* script_engine ) const
			{
#if AS_CAN_USE_CPP11
				asUINT type_traits_flag = asGetTypeTraits< AngelScriptMessageListener<T> >();
#else
				asUINT type_traits_flag = 0;
#endif
				int result = script_engine->RegisterObjectType(getRegisteredName(), sizeof(AngelScriptMessageListener<T>), asOBJ_VALUE | type_traits_flag );
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_CONSTRUCT, "void f(const std::string &in)" , asFUNCTION(MessageListenerRegistrator<T>::constructor), asCALL_CDECL_OBJFIRST);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_DESTRUCT, "void f()" , asFUNCTION(MessageListenerRegistrator<T>::destructor), asCALL_CDECL_OBJFIRST);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectMethod(getRegisteredName(), std::string("void setMessageProcessingCallback(const ?&in)").c_str() , asMETHOD(AngelScriptMessageListener<T>, setMessageProcessingCallback), asCALL_THISCALL );
				
				result = script_engine->RegisterObjectMethod(getRegisteredName(), std::string("void registerAtDispatcher()").c_str() , asMETHOD(AngelScriptMessageListener<T>, registerAtDispatcher), asCALL_THISCALL );
				result = script_engine->RegisterObjectMethod(getRegisteredName(), std::string("void unregisterAtDispatcher()").c_str() , asMETHOD(AngelScriptMessageListener<T>, unregisterAtDispatcher), asCALL_THISCALL );
				
				if(result < 0 ) return false;
				
				return true;
			}
			
			static void constructor(void *memory, const std::string& name)
			{
				new(memory) AngelScriptMessageListener<T>(name);
			}
			
			static void destructor(void *memory)
			{
				static_cast<AngelScriptMessageListener<T>*>(memory)->~AngelScriptMessageListener<T>();
			}
			
			std::string registered_type_name;
			std::string message_type_name;
		};
	}
}