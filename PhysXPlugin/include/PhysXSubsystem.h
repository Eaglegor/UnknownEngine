#pragma once

#include <InlineSpecification.h>
#include <Exception.h>
#include <memory>
#include <unordered_map>
#include <Descriptors/PhysXSubsystemDesc.h>

#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentInterfaces/PhysX/IPhysXSubsystemComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentSystem/BaseComponent.h>
#include <LogHelper.h>
#include <unordered_set>
#include <mutex>

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

		class IPhysXUpdateListener;

		class PhysXErrorCallback;
		
		class PxRigidBodyComponent;
		
		class PhysXSubsystem : 
			public Core::BaseComponent,
			public ComponentInterfaces::UpdateFrameListenerComponent,
			public ComponentInterfaces::IPhysXSubsystemComponent
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(PhysXInitFailed);

			PhysXSubsystem(const char* name, const PhysXSubsystemDesc &desc);
			
			physx::PxPhysics* getPxPhysics() override;
			physx::PxScene* getPxScene() override;
			
			~PhysXSubsystem();

			UNKNOWNENGINE_INLINE
			bool isInitialized(){ return is_initialized; }

			constexpr static const char* getTypeName(){return "PhysXSubsystem";}
			virtual Core::ComponentType getType() const{return getTypeName();}
			
			void init() override;
			void shutdown() override;
			
			virtual void onUpdateFrame(Math::Scalar dt) override;
			
			virtual IComponentInterface* getInterface ( const Core::ComponentType& type );
			
			void addUpdateListener(IPhysXUpdateListener* listener);
			void removeUpdateListener(IPhysXUpdateListener* listener);
			
		private:
			bool is_initialized;

			Core::LogHelper logger;

			physx::PxFoundation* px_foundation;
			physx::PxPhysics* px_physics;
			physx::PxScene* px_scene;
			
			physx::PxCpuDispatcher* px_cpu_dispatcher;
			physx::PxGpuDispatcher* px_gpu_dispatcher;
			physx::PxCudaContextManager* px_cuda_context_manager;
			physx::PxProfileZoneManager* px_profile_zone_manager;
			
			PhysXSubsystemDesc desc;
			
			std::unique_ptr<PhysXErrorCallback> physx_logger;
			
			typedef std::mutex LockPrimitive;
			LockPrimitive update_listeners_lock;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
			
			std::unordered_set<IPhysXUpdateListener*> update_listeners;
			
		};
	}
}