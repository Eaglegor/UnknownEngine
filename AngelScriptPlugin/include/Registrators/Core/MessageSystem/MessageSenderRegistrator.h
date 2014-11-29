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
			registered_type_name("MessageSender<" + message_type_name +">"),
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
				asUINT type_traits_flag = asGetTypeTraits< Core::MessageSender<T> >();
#else
				asUINT type_traits_flag = 0;
#endif
				
				int result = script_engine->RegisterObjectType(getRegisteredName(), sizeof(Core::MessageSender<T>), asOBJ_VALUE | asOBJ_TEMPLATE | type_traits_flag );
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_CONSTRUCT, "void f(const std::string &in, Core::EngineContext@)" , asFUNCTION(MessageSenderRegistrator<T>::constructor), asCALL_CDECL_OBJFIRST);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectBehaviour(getRegisteredName(), asBEHAVE_DESTRUCT, "void f()" , asFUNCTION(MessageSenderRegistrator<T>::destructor), asCALL_CDECL_OBJFIRST);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectMethod(getRegisteredName(), std::string("void sendMessage(const " + message_type_name + "&in)").c_str() , asMETHOD(Core::MessageSender<T>, sendMessage), asCALL_THISCALL );
				if(result < 0 ) return false;
				
				return true;
			}
			
			static void constructor(void *memory, const std::string& name, Core::EngineContext* engine_context)
			{
				new(memory) Core::MessageSender<T>(name, engine_context);
			}
			
			static void destructor(void *memory)
			{
				using namespace Core;
				static_cast<MessageSender<T>*>(memory)->~MessageSender<T>();
			}
			
			std::string registered_type_name;
			std::string message_type_name;
		};
	}
}