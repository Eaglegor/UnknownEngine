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
		static const ComponentMessageTypeId UNKNOWN_MESSAGE_TYPE = static_cast<size_t>(-1);
		typedef std::unordered_map< std::string, float > ComponentMessagePropertiesType;

		class Message
		{
			public:
				Message ( ComponentMessageTypeId type_id )
						: type_id ( type_id )
				{
				}

				virtual ~Message ()
				{
				}

				virtual ComponentMessageTypeId getTypeId ();

				UNKNOWNENGINE_INLINE
				virtual ComponentMessagePropertiesType& getProperties ()
				{
					return properties;
				}

			private:
				ComponentMessageTypeId type_id;
				ComponentMessagePropertiesType properties;
				std::string sender;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
