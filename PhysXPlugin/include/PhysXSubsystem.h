#pragma once

#include <InlineSpecification.h>
#include <Exception.h>
#include <memory>
#include <unordered_map>
#include <Descriptors/PhysXSubsystemDesc.h>

#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>

namespace physx
{
	class PxFoundation;
	class PxPhysics;
	class PxScene;
	class PxCpuDispatcher;
	class PxGpuDispatcher;
	class PxCudaContextManager;
	class PxProfileZoneManager;
}

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class BaseMessageListener;
		class ILogger;
	}

	namespace Physics
	{

		class PhysXErrorCallback;
		
		class PxRigidBodyComponent;
		
		class PhysXSubsystem : public ComponentInterfaces::UpdateFrameListenerComponent
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(PhysXInitFailed);

			PhysXSubsystem(const PhysXSubsystemDesc &desc, Core::EngineContext* engine_context, Core::ILogger* logger);
			
			physx::PxPhysics* getPxPhysics();
			physx::PxScene* getPxScene();
			
			~PhysXSubsystem();

			UNKNOWNENGINE_INLINE
			bool isInitialized(){ return is_initialized; }

			void init();
			void shutdown();
			
			virtual void onUpdateFrame(Math::Scalar dt) override;
			
			void addRigidBodyComponent(const std::string& name, PxRigidBodyComponent* rigid_body_component);
			void removeRigidBodyComponent(const std::string& name);
			PxRigidBodyComponent* getRigidBodyComponent(const std::string &name);

		private:
			bool is_initialized;

			Core::EngineContext* engine_context;
			Core::ILogger* logger;

			physx::PxFoundation* px_foundation;
			physx::PxPhysics* px_physics;
			physx::PxScene* px_scene;
			
			physx::PxCpuDispatcher* px_cpu_dispatcher;
			physx::PxGpuDispatcher* px_gpu_dispatcher;
			physx::PxCudaContextManager* px_cuda_context_manager;
			physx::PxProfileZoneManager* px_profile_zone_manager;
			
			std::unordered_map<std::string, PxRigidBodyComponent*> rigid_body_components;
			
			PhysXSubsystemDesc desc;
			
			std::unique_ptr<PhysXErrorCallback> physx_logger;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
			
		};
	}
}