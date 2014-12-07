#pragma once

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/Policies/Listener/IMessageReceivePolicy.h>
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
			script_engine(nullptr),
			script_context(nullptr),
			callback_function(nullptr),
			registered(false),
			ref_counter(1),
			name(object_name)
			{
			}
			
			virtual ~AngelScriptMessageListener()
			{
				if(registered) unregisterAtDispatcher();
				if(script_context) script_context->Release();
				if(callback_function) callback_function->Release();
				if(script_engine) script_engine->Release();
			}
			
			virtual void setMessageProcessingCallback(void *ref, int typeId)
			{
				callback_function = extractFunction(ref, typeId);
				if(!checkCallbackFunction(callback_function)) return;
				if(!script_context)
				{
					script_engine = callback_function->GetEngine();
					script_engine->AddRef();
					script_context = script_engine->CreateContext();
				}
				//this->callback_function = callback_function;
				callback_function->AddRef();
			}
			
			virtual void processMessage ( const Core::PackedMessage& msg )
			{
				if(callback_function == nullptr || script_context == nullptr) return;
				script_context->Prepare(callback_function);
				MessageType &message = const_cast<MessageType&>(msg.get<MessageType>());
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
			
			static AngelScriptMessageListener<MessageType>* factory(const std::string& name)
			{
				return new AngelScriptMessageListener<MessageType>(name);
			}
			
			void Addref()
			{
				++ref_counter;
			}
			
			void Release()
			{
				if(--ref_counter == 0) 
				{
					std::cout << "Deleting object" << std::endl;
					delete this;
				}
			}
			
			const char* getName() const override
			{
				return name.c_str();
			}
			
		private:
			
			asIScriptFunction* extractFunction(void* ref, int typeId)
			{
				asIScriptFunction* func = static_cast<asIScriptFunction*>(ref);
				return func;
			}
			
			bool checkCallbackFunction(asIScriptFunction* function)
			{
				if(function == nullptr) return false;
				return true;
			}
			
			asIScriptEngine *script_engine;
			asIScriptContext *script_context;
			asIScriptFunction *callback_function;
			
			bool registered;
			size_t ref_counter;
			std::string name;
		};
	}
}