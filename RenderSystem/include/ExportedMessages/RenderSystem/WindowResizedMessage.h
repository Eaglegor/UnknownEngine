#pragma once

#include <MessageSystem/TypeCachingMessagePacker.h>
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/PackedMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class WindowResizedMessagePacker;
		class WindowResizedMessageUnpacker;

		struct WindowResizedMessage
		{
			typedef WindowResizedMessagePacker PackerClass;
			typedef WindowResizedMessageUnpacker UnpackerClass;

			static std::string getTypeName()
			{
				return "Graphics.GUI.WindowResizedMessage";
			}

			std::string window_name;
			size_t width;
			size_t height;
		};

		class WindowResizedMessagePacker : public Core::TypeCachingMessagePacker<WindowResizedMessage>
		{
		public:
				WindowResizedMessagePacker ( const Core::MessageSystemParticipantId& sender_info ) :
					TypeCachingMessagePacker< UnknownEngine::Graphics::WindowResizedMessage > ( sender_info ) {}

				virtual Core::PackedMessage packMessage ( const WindowResizedMessage& msg )
				{
					Core::PackedMessage result ( getMessageType(), sender_info );
					result.getProperties().set<std::string>("window_name", msg.window_name);
					result.getProperties().set<int> ( "width", msg.width );
					result.getProperties().set<int> ( "height", msg.height );
					return result;
				}
		};

		class WindowResizedMessageUnpacker : public Core::MessageUnpacker<WindowResizedMessage>
		{
		public:
				virtual WindowResizedMessage unpackMessage ( const Core::PackedMessage& msg )
				{
					WindowResizedMessage result;
					result.window_name = msg.getProperties().get<std::string>("window_name");
					result.width = msg.getProperties().get<int>("width");
					result.height = msg.getProperties().get<int>("height");
					return result;
				}
		};

	}
}
