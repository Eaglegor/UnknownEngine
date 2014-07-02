#ifndef UNKNOWNENGINE_CORE_ENGINECONTEXT_H
#define UNKNOWNENGINE_CORE_ENGINECONTEXT_H

#include <InlineSpecification.h>

namespace UnknownEngine {

	namespace Core {

		class ComponentsManager;
		class MessageDictionary;
		class MessageDispatcher;
		class ResourceManager;

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

			private:
				friend class Engine;
				ComponentsManager* components_manager;
				ResourceManager* resource_manager;
				MessageDictionary* message_dictionary;
				MessageDispatcher* message_dispatcher;
		};

	} // namespace Core
} // namespace UnknownEngine

#endif // UNKNOWNENGINE_CORE_ENGINECONTEXT_H
