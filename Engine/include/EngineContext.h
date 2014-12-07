#pragma once
#include <InlineSpecification.h>

namespace UnknownEngine
{

	namespace Core
	{

		class LogManager;
		class ComponentsManager;
		class MessageDispatcher;
		class ResourceManager;

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
				MessageDispatcher* getMessageDispatcher()
				{
					return message_dispatcher;
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
				MessageDispatcher* message_dispatcher;
				LogManager* log_manager;
		};

	} // namespace Core
} // namespace UnknownEngine
