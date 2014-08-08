#pragma once
/*
 * IMessageListener.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <ComponentSystem_export.h>
#include <string>
#include <InlineSpecification.h>
#include <MessageSystem/IMessageSystemParticipant.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PackedMessage;

		/**
		 * @brief Base class for all message listeners
		 *
		 * ###Concept
		 *
		 * The only expected way to communicate between subsystems in Unknown %Engine is to use messages.
		 * You can send messages from any place of code but only listeners can receive messages.
		 * IMessageListener class defines the interface for listeners.
		 *
		 */
		class IMessageListener : public IMessageSystemParticipant
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION ( MessageTypeNotSupportedByListener );

				/**
				 * @brief Constructor
				 *
				 * To get an address on a message bus the listener must have **unique** name.
				 *
				 * @param object_name - **unique** name for message listener
				 */
				COMPONENTSYSTEM_EXPORT
				IMessageListener ( const std::string &object_name );

				COMPONENTSYSTEM_EXPORT
				virtual ~IMessageListener ();

				/**
				 * @brief Compares a listener to another listener using it's id
				 * @param rhs - Listener to compare to
				 * @return true if ids are equal
				 */
				bool operator== ( const IMessageListener &rhs ) const
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
