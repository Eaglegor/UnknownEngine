#pragma once
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/TypeCachingMessagePacker.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		class AddRenderWindowCallbacksMessagePacker;
		class AddRenderWindowCallbacksMessageUnpacker;
		
		struct AddRenderWindowCallbackMessage
		{
			
		};
		
		class AddRenderWindowCallbackMessagePacker : public Core::TypeCachingMessagePacker<AddRenderWindowCallbackMessage>
		{
		public:
				AddRenderWindowCallbackMessagePacker ( const Core::MessageSystemParticipantId& sender_info ):
				Core::TypeCachingMessagePacker<AddRenderWindowCallbackMessage>(sender_info)
				{}
				
				virtual Core::PackedMessage packMessage ( const AddRenderWindowCallbackMessage& msg )
				{
					Core::PackedMessage result ( getMessageType(), sender_info );
					
					return result;
				}
		};
		
		class AddRenderWindowCallbackMessageUnpacker
		{
			
		};
		
	}
}
