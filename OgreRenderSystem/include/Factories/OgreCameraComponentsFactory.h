#pragma once

#include <IComponentFactory.h>
#include <ComponentDesc.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Exception.h>
#include <Factories/BaseOgreComponentFactory.h>
#include <OgreRenderSubsystem_fwd.h>

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

		class OgreCameraComponent;

		/**
		 * @brief Factory for creating solid and compound non-deformable (mesh doesn't change during the whole lifetime) renderable components
		 */
		class OgreCameraComponentsFactory: public BaseOgreComponentFactory
		{
			public:

				OgreCameraComponentsFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext *engine_context, Core::LogHelper* log_helper = nullptr );

				virtual const std::string getName();
				virtual const std::unordered_set<Core::ComponentType>& getSupportedTypes();
				virtual const bool supportsType ( const Core::ComponentType &object_type );

			protected:
				virtual Core::Component* internalCreateObject ( const Core::ComponentDesc& desc );
				virtual void internalDestroyObject ( Core::Component* object );
				
			private:
				// Solid renderable components
				Core::Component* createCameraComponent ( const Core::ComponentDesc &desc );
				void destroyCameraComponent ( const Core::Component* component );
				void registerCameraComponentListeners ( OgreCameraComponent* component, const Core::ReceivedMessageDescriptorsList &received_messages );
 				
		};

	} // namespace Graphics
} // namespace UnknownEngine
