#pragma once

#include <string>

#include <InlineSpecification.h>
#include <MessageSystem/TypeCachingMessagePacker.h>
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>

#include <Keys.h>

namespace UnknownEngine
{
	namespace IO
	{

		class KeyStateChangedMessagePacker;
		class KeyStateChangedMessageUnpacker;

		/**
		 * @brief Key pressed message
		 *
		 * Indicates that the key is pressed
		 * 
		 */

		struct KeyStateChangedMessage
		{

			typedef KeyStateChangedMessagePacker PackerClass;
			typedef KeyStateChangedMessageUnpacker UnpackerClass;

			UNKNOWNENGINE_INLINE
			static std::string getTypeName()
			{
				return "IO.KeyStateChanged";
			}

			KeyState new_state;
			Key key;
		};

		/**
		 * @brief Message packer for LogMessage
		 */
		class KeyStateChangedMessagePacker: public Core::TypeCachingMessagePacker<KeyStateChangedMessage>
		{
			public:

				KeyStateChangedMessagePacker ( const Core::MessageSystemParticipantId &sender_info ) :
					Core::TypeCachingMessagePacker<KeyStateChangedMessage> ( sender_info )
				{
				}

				UNKNOWNENGINE_INLINE
				Core::PackedMessage packMessage ( const KeyStateChangedMessage& msg ) override
				{
					Core::PackedMessage result ( getMessageType(), sender_info );
					result.getProperties().set<KeyState>("new_state", msg.new_state);
					result.getProperties().set<Key>("key", msg.key);
					return result;
				}

		};

		/**
		 * @brief Message unpacker for LogMessage
		 */
		class KeyStateChangedMessageUnpacker: public Core::MessageUnpacker<KeyStateChangedMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				KeyStateChangedMessage unpackMessage ( const Core::PackedMessage &msg )
				throw ( Core::InvalidMessageFormatException ) override
				{
					KeyStateChangedMessage result;
					result.new_state = msg.getProperties().get<KeyState>("new_state");
					result.key = msg.getProperties().get<Key>("key");
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
