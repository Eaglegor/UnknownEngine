#pragma once
/*
 * IMessageListener.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>
#include <InlineSpecification.h>
#include <MessageSystem/IMessageSystemParticipant.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PackedMessage;

		/**
		 * @brief Base class for all message listeners
		 *
		 * Is a message system participant.
		 *
		 */
		class IMessageListener : public IMessageSystemParticipant
		{
			public:
				/**
				 * @brief Constructor
				 *
				 * Message listener is a message system participant so it must have a unique message system participant identifier
				 *
				 * @param object_name - **unique** name for message listener
				 */
				IMessageListener (const std::string &object_name);
				virtual ~IMessageListener ();

				/**
				 * @brief Compares a listener to another listener using it's id
				 * @param rhs - Listener to compare to
				 * @return true if ids are equal
				 */
				virtual bool operator== ( const IMessageListener &rhs ) const
				{
					return getMessageSystemParticipantId() == rhs.getMessageSystemParticipantId();
				}

				/**
				 * @brief Message handler
				 * @param msg - packed message to process
				 */
				virtual void processMessage ( const PackedMessage &msg ) = 0;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
