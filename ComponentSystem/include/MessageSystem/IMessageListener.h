#pragma once
/*
 * IMessageListener.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <string>

namespace UnknownEngine
{
	namespace Core
	{

		class Message;
		class IMessageReceivePolicy;

		class IMessageListener
		{
			public:
				IMessageListener ();
				virtual ~IMessageListener ();

				virtual bool operator== ( const IMessageListener &rhs ) const
				{
					return getName() == rhs.getName();
				}

				virtual std::string getName () const = 0;
				virtual void processMessage ( const Message &msg ) = 0;
				virtual IMessageReceivePolicy* getMessageReceivePolicy () const;
				virtual void setMessageReceivePolicy ( IMessageReceivePolicy* policy );

			private:
				IMessageReceivePolicy* message_receive_policy;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
