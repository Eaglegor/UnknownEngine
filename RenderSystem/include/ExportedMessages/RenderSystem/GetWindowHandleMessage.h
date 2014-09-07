#pragma once

#include <MessageSystem/TypeCachingMessagePacker.h>
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <MessageSystem/PackedMessage.h>
#include <WindowHandle.h>
#include <string>
#include <functional>

namespace UnknownEngine
{
	namespace Graphics
	{
		class GetWindowHandleMessagePacker;
		class GetWindowHandleMessageUnpacker;
		
		struct GetWindowHandleMessage
		{
			typedef GetWindowHandleMessagePacker PackerClass;
			typedef GetWindowHandleMessageUnpacker UnpackerClass;
			
			static std::string getTypeName()
			{
				return "Graphics.GUI.GetWindowHandleMessage";
			}
			
			std::string requested_window_name;
			std::function<void(const NativeWindowHandleType&)> result_callback;
			
		};
		
		class GetWindowHandleMessagePacker : public Core::TypeCachingMessagePacker<GetWindowHandleMessage>
		{
		public:
			GetWindowHandleMessagePacker( const Core::MessageSystemParticipantId &sender_info ):
			Core::TypeCachingMessagePacker<GetWindowHandleMessage>(sender_info){}
			
			virtual Core::PackedMessage packMessage ( const GetWindowHandleMessage& msg )
			{
				Core::PackedMessage result(getMessageType(), sender_info);
				result.getProperties().set<std::string>("requested_window_name", msg.requested_window_name);
				result.getProperties().set< std::function<void(const NativeWindowHandleType&)> >("result_callback", msg.result_callback);
				return result;
			}
			
		};
		
		class GetWindowHandleMessageUnpacker : public Core::MessageUnpacker<GetWindowHandleMessage>
		{
		public:
			
			virtual GetWindowHandleMessage unpackMessage ( const Core::PackedMessage& msg )
			{
				GetWindowHandleMessage result;
				result.requested_window_name = msg.getProperties().get<std::string>("requested_window_name");
				result.result_callback = msg.getProperties().get< std::function< void(const NativeWindowHandleType&)> >("result_callback");
				return result;
			}
			
		};
		
	}
}