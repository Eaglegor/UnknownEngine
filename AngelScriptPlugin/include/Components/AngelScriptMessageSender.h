#pragma once

#include <MessageSystem/MessageSender.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		template<typename MessageClass>
		class AngelScriptMessageSender
		{
		public:
			AngelScriptMessageSender(const std::string &name, Core::EngineContext* engine_context):
			message_sender(name, engine_context),
			ref_counter(1)
			{
			}
			
			void sendMessage(const MessageClass& msg)
			{
				message_sender.sendMessage(msg);
			}

			static AngelScriptMessageSender<MessageClass>* factory(const std::string &name, Core::EngineContext* engine_context)
			{
				return new AngelScriptMessageSender<MessageClass>(name, engine_context);
			}
			
			void Addref()
			{
				++ref_counter;
			}
			
			void Release()
			{
				if(--ref_counter == 0) delete this;
			}
			
		private:
			Core::MessageSender<MessageClass> message_sender;
			size_t ref_counter;
		};
	}
}