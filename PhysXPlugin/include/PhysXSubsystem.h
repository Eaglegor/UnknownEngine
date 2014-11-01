#pragma once

#include <InlineSpecification.h>
#include <Exception.h>
#include <memory>
#include <unordered_map>

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
		struct UpdateFrameMessage;
	}

	namespace Utils
	{
		class LogHelper;
	}
	
	namespace Physics
	{
		
		class PxRigidBodyComponent;
		
		class PhysXSubsystem
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(PhysXInitFailed);

			PhysXSubsystem(Core::EngineContext* engine_context, Utils::LogHelper* log_helper);
			
			physx::PxPhysics* getPxPhysics();
			physx::PxScene* getPxScene();
			
			~PhysXSubsystem();

			UNKNOWNENGINE_INLINE
			bool isInitialized(){ return is_initialized; }

			void init();
			void shutdown();
			
			void onUpdateFrame(const Core::UpdateFrameMessage &msg);
			
			void addRigidBodyComponent(const std::string& name, PxRigidBodyComponent* rigid_body_component);
			void removeRigidBodyComponent(const std::string& name);
			PxRigidBodyComponent* getRigidBodyComponent(const std::string &name);

		private:
			bool is_initialized;

			Core::EngineContext* engine_context;
			Utils::LogHelper* log_helper;

			physx::PxFoundation* px_foundation;
			physx::PxPhysics* px_physics;
			physx::PxScene* px_scene;
			
			physx::PxCpuDispatcher* px_cpu_dispatcher;
			physx::PxGpuDispatcher* px_gpu_dispatcher;
			physx::PxCudaContextManager* px_cuda_context_manager;
			physx::PxProfileZoneManager* px_profile_zone_manager;
			
			std::unordered_map<std::string, PxRigidBodyComponent*> rigid_body_components;
			
		};
	}
}