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
			message_type_name(message_type_name),
			full_name("Core::"+registered_type_name)
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

			virtual const char* getRegisteredNameWithNamespace() const override
			{
				return full_name.c_str();
			}
			
		private:
			
			bool registerTypeImpl ( asIScriptEngine* script_engine ) const
			{
				int result = script_engine->RegisterObjectType(getRegisteredName(), 0, asOBJ_REF );
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_FACTORY, (registered_type_name+"@ f(const std::string &in)").c_str(), asFUNCTION(AngelScriptMessageListener<T>::factory), asCALL_CDECL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_ADDREF, "void f()" , asMETHOD(AngelScriptMessageListener<T>, Addref), asCALL_THISCALL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_RELEASE, "void f()" , asMETHOD(AngelScriptMessageListener<T>, Release), asCALL_THISCALL);
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
			
			const std::string registered_type_name;
			const std::string message_type_name;
			const std::string full_name;
			
		};
	}
}