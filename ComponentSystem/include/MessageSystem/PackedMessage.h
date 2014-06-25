#pragma once
/*
 * Message.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>
#include <unordered_map>

#include <InlineSpecification.h>
#include <Properties/Properties.h>
#include <MessageSystem/SenderInfo.h>

namespace UnknownEngine
{
	namespace Core
	{

		typedef size_t ComponentMessageTypeId;
		static const ComponentMessageTypeId UNKNOWN_MESSAGE_TYPE = static_cast< size_t > ( -1 );

		class PackedMessage
		{
			public:
				PackedMessage ( ComponentMessageTypeId type_id, SenderInfo sender_info )
						: type_id ( type_id ), sender_info ( sender_info )
				{
				}

				virtual ~PackedMessage ()
				{
				}

				UNKNOWNENGINE_INLINE
				virtual ComponentMessageTypeId getTypeId () const
				{
					return type_id;
				}

				UNKNOWNENGINE_INLINE
				SenderInfo getSenderInfo () const
				{
					return sender_info;
				}

				UNKNOWNENGINE_INLINE
				Properties &getProperties ()
				{
					return properties;
				}

				UNKNOWNENGINE_INLINE
				const Properties &getProperties () const
				{
					return properties;
				}

			private:
				ComponentMessageTypeId type_id;
				Properties properties;
				SenderInfo sender_info;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
