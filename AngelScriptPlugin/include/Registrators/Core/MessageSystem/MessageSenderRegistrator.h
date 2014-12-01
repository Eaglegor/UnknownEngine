#pragma once

#include <Registrators/ITypeRegistrator.h>
#include <Components/AngelScriptMessageSender.h>
#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		template<typename T>
		class MessageSenderRegistrator : public ITypeRegistrator
		{
		public:
			MessageSenderRegistrator(const std::string &message_type_name):
			registered_type_name("MessageSender<" + message_type_name +">"),
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

			virtual const char* getRegisteredNameWithNamespace() const
			{
				return full_name.c_str();
			}
			
		private:
			
			bool registerTypeImpl ( asIScriptEngine* script_engine ) const
			{
				int result = script_engine->RegisterObjectType(getRegisteredName(), 0, asOBJ_REF );
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_FACTORY, (registered_type_name + "@ f(const std::string &in, Core::EngineContext@)").c_str(), asFUNCTION(AngelScriptMessageSender<T>::factory), asCALL_CDECL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_ADDREF, "void f()" , asMETHOD(AngelScriptMessageSender<T>, Addref), asCALL_THISCALL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_RELEASE, "void f()" , asMETHOD(AngelScriptMessageSender<T>, Release), asCALL_THISCALL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectMethod(getRegisteredName(), std::string("void sendMessage(const " + message_type_name + "&in)").c_str() , asMETHOD(Core::MessageSender<T>, sendMessage), asCALL_THISCALL );
				if(result < 0 ) return false;
				
				return true;
			}
			
			const std::string registered_type_name;
			const std::string message_type_name;
			const std::string full_name;
		};
	}
}