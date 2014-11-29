#pragma once

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/MessageDispatcher.h>
#include <ASIncludes.h>
#include <MessageBuffers/MessageBuffer.h>

namespace UnknownEngine
{

	namespace Behavior
	{
		template<typename MessageType>
		class AngelScriptMessageListener : public Core::IMessageListener
		{
		public:
			AngelScriptMessageListener (const std::string& object_name):
			Core::IMessageListener(object_name),
			script_engine(nullptr),
			script_context(nullptr),
			callback_function(nullptr),
			registered(false)
			{}
			
			virtual ~AngelScriptMessageListener()
			{
				if(registered) unregisterAtDispatcher();
				if(script_context) script_context->Release();
				if(callback_function) callback_function->Release();
				if(script_engine) script_engine->Release();
			}
			
			virtual void setScriptEngine(asIScriptEngine* script_engine)
			{
				this->script_engine = script_engine;
				script_engine->AddRef();
				script_context = script_engine->CreateContext();
			}
			
			virtual void setMessageProcessingCallback(asIScriptFunction *callback_function)
			{
				this->callback_function = callback_function;
				callback_function->AddRef();
			}
			
			virtual void processMessage ( const Core::PackedMessage& msg )
			{
				if(callback_function == nullptr || script_context == nullptr) return;
				script_context->Prepare(callback_function);
				MessageType &message = const_cast<MessageType&>(msg.get<MessageType>());
				script_context->SetObject(callback_function->GetDelegateObject());
				script_context->SetArgObject(0, &message);
				script_context->Execute();
			}
			
			virtual void registerAtDispatcher()
			{
				Core::MessageDispatcher::getSingleton()->addListener(MESSAGE_TYPE_ID(MessageType::getTypeName()), this);
				registered = true;
			}
			
			virtual void unregisterAtDispatcher()
			{
				Core::MessageDispatcher::getSingleton()->removeListener(this);
				registered = false;
			}
			
		private:
			
			asIScriptEngine *script_engine;
			asIScriptContext *script_context;
			asIScriptFunction *callback_function;
			
			bool registered;
		};
	}
}