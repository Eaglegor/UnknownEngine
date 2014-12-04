#ifndef UNKNOWNENGINE_CORE_ENGINECONTEXT_H
#define UNKNOWNENGINE_CORE_ENGINECONTEXT_H

#include <InlineSpecification.h>

namespace UnknownEngine
{

	namespace Core
	{
		class ComponentsManager;
		class MessageDictionary;
		class MessageDispatcher;
		class ResourceManager;
		class MessageSystemParticipantDictionary;
		class MessagingPoliciesManager;

		/**
		 * @brief Engine context holds pointers to core engine's subsystems
		 */
		class EngineContext
		{
			public:
				/// Returns the components manager
				UNKNOWNENGINE_INLINE
				ComponentsManager* getComponentsManager()
				{
					return components_manager;
				}

				/// Returns resource manager
				UNKNOWNENGINE_INLINE
				ResourceManager* getResourceManager()
				{
					return resource_manager;
				}

				/// Returns message dictionary
				UNKNOWNENGINE_INLINE
				MessageDictionary* getMessageDictionary()
				{
					return message_dictionary;
				}

				/// Returns message dispatcher
				UNKNOWNENGINE_INLINE
				MessageDispatcher* getMessageDispatcher()
				{
					return message_dispatcher;
				}

				/// Returns message system participant dictionary (address book)
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
				
			private:
				friend class Engine;

				ComponentsManager* components_manager; ///< Components manager
				ResourceManager* resource_manager; ///< Resource manager
				MessageDictionary* message_dictionary; ///< Message dictionary
				MessageDispatcher* message_dispatcher; ///< Message dispatcher
				/// Message system participant dictionary (address book)
				MessageSystemParticipantDictionary* message_system_participant_dictionary;
				MessagingPoliciesManager* messaging_policies_manager;
		};

	} // namespace Core
} // namespace UnknownEngine

#endif // UNKNOWNENGINE_CORE_ENGINECONTEXT_H
