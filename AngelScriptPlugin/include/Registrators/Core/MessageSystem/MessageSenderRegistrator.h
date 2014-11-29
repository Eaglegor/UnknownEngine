#pragma once

#include <Registrators/ITypeRegistrator.h>
#include <MessageSystem/MessageSender.h>
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
			registered_type_name("MessageSender" + "<" + message_type_name +">"),
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
				
				bool success = registerTypeImpl();
				
				script_engine->SetDefaultNamespace("");
				
				return success;
			}

		private:
			
			bool registerTypeImpl ( asIScriptEngine* script_engine ) const
			{
				int result = script_engine->RegisterObjectType(getRegisteredName(), sizeof(Core::MessageSender<T>), asOBJ_VALUE | asOBJ_TEMPLATE | asGetTypeTraits< Core::MessageSender<T> >() );
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_CONSTRUCT, "void f(const std::string &in, Core::EngineContext@)" , asFUNCTION(MessageSenderRegistrator<T>::constructor));
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_DESTRUCT, "void f()" , asFUNCTION(MessageSenderRegistrator<T>::destructor));
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void sendMessage(const " + message_type_name + "&in)" , asMETHOD(Core::MessageSender<T>, sendMessage), asCALL_THISCALL );
				if(result < 0 ) return false;
				
				return true;
			}
			
			static void constructor(void *memory, const std::string& name, Core::EngineContext* engine_context)
			{
				new(memory) Core::MessageSender<T>(name, engine_context);
			}
			
			static void destructor(void *memory)
			{
				static_cast<Core::MessageSender<T>*>(memory)->~Core::MessageSender<T>();
			}
			
			std::string registered_type_name;
			std::string message_type_name;
		};
	}
}