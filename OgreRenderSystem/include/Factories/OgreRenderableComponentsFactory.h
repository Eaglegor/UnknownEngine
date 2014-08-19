#pragma once

#include <OgreRenderSubsystem_fwd.h>
#include <IComponentFactory.h>
#include <ComponentDesc.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Exception.h>
#include <Factories/BaseOgreComponentFactory.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
		class IMessageListener;
		struct ReceivedMessageDesc;
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreRenderableComponent;

		/**
		 * @brief Factory for creating solid and compound non-deformable (mesh doesn't change during the whole lifetime) renderable components
		 */
		class OgreRenderableComponentsFactory: public BaseOgreComponentFactory
		{
			public:

				OgreRenderableComponentsFactory ( OgreRenderSubsystem* render_system, Core::EngineContext *engine_context, Core::LogHelper* log_helper = nullptr );
				virtual ~OgreRenderableComponentsFactory();

				virtual const std::string getName();
				virtual const std::unordered_set<Core::ComponentType>& getSupportedTypes();
				virtual const bool supportsType ( const Core::ComponentType &object_type );
				virtual Core::Component* createObject ( const Core::ComponentDesc& desc );

			protected:
				virtual void internalDestroyObject ( Core::Component* object );

			private:
				// Solid renderable components
				Core::Component* createRenderableComponent ( const Core::ComponentDesc &desc );
				void destroyRenderableComponent ( const Core::Component* component );
				void registerRenderableComponentListeners ( OgreRenderableComponent* component, const Core::ReceivedMessageDescriptorsList &received_messages );
		};

	} // namespace Graphics
} // namespace UnknownEngine
