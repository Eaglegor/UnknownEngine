#ifndef UNKNOWNENGINE_CORE_ENGINECONTEXT_H
#define UNKNOWNENGINE_CORE_ENGINECONTEXT_H

#include <InlineSpecification.h>

namespace UnknownEngine {

	namespace Core {

		class ComponentsManager;
		class MessageDictionary;
		class MessageDispatcher;
		class ResourceManager;
		class MessageSystemParticipantDictionary;

		/**
		 * @brief Engine context holds pointers to core engine's subsystems
		 */
		class EngineContext
		{
			public:
				UNKNOWNENGINE_INLINE
				ComponentsManager* getComponentsManager(){return components_manager;}

				UNKNOWNENGINE_INLINE
				ResourceManager* getResourceManager(){return resource_manager;}

				UNKNOWNENGINE_INLINE
				MessageDictionary* getMessageDictionary(){return message_dictionary;}

				UNKNOWNENGINE_INLINE
				MessageDispatcher* getMessageDispatcher(){return message_dispatcher;}

				UNKNOWNENGINE_INLINE
				MessageSystemParticipantDictionary* getMessageSystemParticipantDictionary(){return message_system_participant_dictionary;}

			private:
				friend class Engine;

				ComponentsManager* components_manager;
				ResourceManager* resource_manager;
				MessageDictionary* message_dictionary;
				MessageDispatcher* message_dispatcher;
				MessageSystemParticipantDictionary* message_system_participant_dictionary;
		};

	} // namespace Core
} // namespace UnknownEngine

#endif // UNKNOWNENGINE_CORE_ENGINECONTEXT_H
