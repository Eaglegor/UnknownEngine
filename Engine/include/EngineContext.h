#pragma once
#include <InlineSpecification.h>

namespace UnknownEngine
{

	namespace Core
	{

		class LogManager;
		class ComponentsManager;
		class MessageDictionary;
		class MessageDispatcher;
		class ResourceManager;
		class MessageSystemParticipantDictionary;
		class MessagingPoliciesManager;

		class EngineContext
		{
			public:
				UNKNOWNENGINE_INLINE
				ComponentsManager* getComponentsManager()
				{
					return components_manager;
				}

				UNKNOWNENGINE_INLINE
				ResourceManager* getResourceManager()
				{
					return resource_manager;
				}

				UNKNOWNENGINE_INLINE
				MessageDictionary* getMessageDictionary()
				{
					return message_dictionary;
				}

				UNKNOWNENGINE_INLINE
				MessageDispatcher* getMessageDispatcher()
				{
					return message_dispatcher;
				}

				UNKNOWNENGINE_INLINE
				MessageSystemParticipantDictionary* getMessageSystemParticipantDictionary()
				{
					return message_system_participant_dictionary;
				}

				UNKNOWNENGINE_INLINE
				MessagingPoliciesManager* getMessagingPoliciesManager()
				{
					return messaging_policies_manager;
				}
				
				UNKNOWNENGINE_INLINE
				LogManager* getLogManager()
				{
					return log_manager;
				}
				
			private:
				friend class Engine;

				ComponentsManager* components_manager;
				ResourceManager* resource_manager;
				MessageDictionary* message_dictionary;
				MessageDispatcher* message_dispatcher;
				MessageSystemParticipantDictionary* message_system_participant_dictionary;
				MessagingPoliciesManager* messaging_policies_manager;
				LogManager* log_manager;
		};

	} // namespace Core
} // namespace UnknownEngine
