#pragma once

/*
 * AnyMessageReceivePolicy.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

#include <ComponentSystem_export.h>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/Policies/MessagePolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief \ref IMessageReceivePolicy "Receive policy" allowing any message to be processed
		 */

		class AnyMessageReceivePolicy : public IMessageReceivePolicy
		{
			public:
				/**
				 * @brief Always returns true
				 * @param msg - Message to analyze
				 * @return true
				 */
				COMPONENTSYSTEM_EXPORT
				virtual bool acceptMessage(const PackedMessage &msg) override;

				static const MessagePolicyType getType(){return "AnyMessageReceivePolicy";}

				virtual ~AnyMessageReceivePolicy (){}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
