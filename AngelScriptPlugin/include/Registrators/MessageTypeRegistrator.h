#pragma once

#include <Registrators/ClassValueTypeRegistrator.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		template<typename MessageClass>
		class MessageTypeRegistrator : public ClassValueTypeRegistrator<MessageClass>
		{
		public:
			MessageTypeRegistrator(const std::string& registered_name, const std::string& declaration_namespace):
			ClassValueTypeRegistrator<MessageClass>(registered_name, declaration_namespace)
			{
			}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const override
			{
				bool success = ClassValueTypeRegistrator<MessageClass>::registerType(script_engine);
				if(!success) return false;
				
				script_engine->SetDefaultNamespace(ClassValueTypeRegistrator<MessageClass>::getRegisteredNameWithNamespace());
					
				int result = script_engine->RegisterGlobalFunction("int getType()", asFUNCTION(MessageTypeRegistrator<MessageClass>::getMessageType), asCALL_CDECL);
				success = success && (result >= 0);
				
				result = script_engine->RegisterGlobalFunction("std::string getTypeName()", asFUNCTION(MessageTypeRegistrator<MessageClass>::getMessageTypeName), asCALL_CDECL);
				success = success && (result >= 0);
				
				script_engine->SetDefaultNamespace("");
				
				return success;
			}
			
			static Core::MessageType getMessageType()
			{
				return MESSAGE_TYPE_ID(MessageClass::getTypeName());
			}
			
			static std::string getMessageTypeName()
			{
				return std::string(MessageClass::getTypeName());
			}
		};
	}
}