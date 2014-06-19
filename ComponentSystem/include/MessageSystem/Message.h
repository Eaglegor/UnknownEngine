#pragma once
/*
 * Message.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <string>
#include <unordered_map>

#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{

		typedef size_t ComponentMessageTypeId;
		static const ComponentMessageTypeId UNKNOWN_MESSAGE_TYPE = static_cast< size_t > ( -1 );
		typedef std::unordered_map< std::string, float > ComponentMessagePropertiesType;

		class Message
		{
			public:
				Message ( ComponentMessageTypeId type_id, std::string sender_name )
						: type_id ( type_id ), sender_name ( sender_name )
				{
				}

				virtual ~Message ()
				{
				}

				UNKNOWNENGINE_INLINE
				virtual ComponentMessageTypeId getTypeId () const
				{
					return type_id;
				}

				UNKNOWNENGINE_INLINE
				virtual ComponentMessagePropertiesType& getProperties ()
				{
					return properties;
				}

				UNKNOWNENGINE_INLINE
				std::string getSenderName () const
				{
					return sender_name;
				}

			private:
				ComponentMessageTypeId type_id;
				ComponentMessagePropertiesType properties;
				std::string sender_name;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
