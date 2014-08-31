#pragma once

#include <InlineSpecification.h>
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/TypeCachingMessagePacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>
#include <NumericIdentifierType.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class ChangeMaterialActionMessagePacker;
		class ChangeMaterialActionMessageUnpacker;

		/**
		 * @brief Command to change entity's material
		 *
		 */
		struct ChangeMaterialActionMessage
		{

			typedef ChangeMaterialActionMessagePacker PackerClass;
			typedef ChangeMaterialActionMessageUnpacker UnpackerClass;

			UNKNOWNENGINE_INLINE
			static std::string getTypeName()
			{
				return "Graphics.ChangeMaterialActionMessage";
			}

			std::string new_material_name;
		};

		/**
		 * @brief Message packer for UpdateFrameMessage
		 */
		class ChangeMaterialActionMessagePacker: public Core::TypeCachingMessagePacker<ChangeMaterialActionMessage>
		{
			public:

				ChangeMaterialActionMessagePacker ( Core::MessageSystemParticipantId sender_info ) :
					Core::TypeCachingMessagePacker<ChangeMaterialActionMessage> ( sender_info )
				{
				}

				UNKNOWNENGINE_INLINE
				Core::PackedMessage packMessage ( const ChangeMaterialActionMessage& msg ) override
				{
					Core::PackedMessage result ( getMessageType(), sender_info );
					return result;
				}

		};

		/**
		 * @brief Message unpacker for UpdateFrameMessage
		 */
		class ChangeMaterialActionMessageUnpacker: public Core::MessageUnpacker<ChangeMaterialActionMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				ChangeMaterialActionMessage unpackMessage ( const Core::PackedMessage &msg ) throw ( Core::InvalidMessageFormatException ) override
				{
					ChangeMaterialActionMessage result;
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
