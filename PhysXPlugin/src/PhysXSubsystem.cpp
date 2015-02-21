#include <stdafx.h>
#include <PhysXSubsystem.h>

using std::isfinite;

#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <Logging.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <pxtask/PxCudaContextManager.h>
#include <Components/PxRigidBodyComponent.h>
#include <PhysXErrorCallback.h>
#include <Converters/PxVec3Converter.h>

static physx::PxDefaultAllocator gDefaultAllocatorCallback;

static physx::PxSimulationFilterShader default_simulation_filter_shader = &physx::PxDefaultSimulationFilterShader;

namespace UnknownEngine
{
	namespace Physics
	{
		PhysXSubsystem::PhysXSubsystem ( const PhysXSubsystemDesc& desc, Core::EngineContext* engine_context, Core::ILogger* logger ) :
			is_initialized ( false ),
			engine_context ( engine_context ),
			logger ( logger ),
			px_foundation ( nullptr ),
			px_physics ( nullptr ),
			px_scene ( nullptr ),
			px_cpu_dispatcher ( nullptr ),
			px_gpu_dispatcher ( nullptr ),
			px_cuda_context_manager ( nullptr ),
			px_profile_zone_manager ( nullptr ),
			desc(desc),
			update_frame_provider(desc.update_frame_provider)
		{
		}

		void PhysXSubsystem::init()
		{
			physx_logger.reset(new PhysXErrorCallback(logger));
			
			px_foundation = PxCreateFoundation ( PX_PHYSICS_VERSION, gDefaultAllocatorCallback, *physx_logger );
			if ( px_foundation == nullptr )
			{
				LOG_ERROR ( logger, "Failed to create PxFoundation object. PhysX not initialized" );
			}
			else
			{
				LOG_INFO ( logger, "PxFoundation initialized" );
				
				if(desc.enable_profiling)
				{
					px_profile_zone_manager = &physx::PxProfileZoneManager::createProfileZoneManager ( px_foundation );
					if ( px_profile_zone_manager == nullptr )
					{
						LOG_ERROR ( logger, "Failed to create PxProfileZoneManager. Profiling not enabled" );
					}
				}
				
				physx::PxTolerancesScale tolerance_scale;
				if(desc.length_tolerance_scale) tolerance_scale.length = desc.length_tolerance_scale.get();
				if(desc.mass_tolerance_scale) tolerance_scale.mass = desc.mass_tolerance_scale.get();
				if(desc.speed_tolerance_scale) tolerance_scale.speed = desc.speed_tolerance_scale.get();
				
				px_physics = PxCreatePhysics ( PX_PHYSICS_VERSION, *px_foundation, tolerance_scale, desc.track_outstanding_allocations, px_profile_zone_manager );
				if ( px_physics == nullptr )
				{
					LOG_ERROR ( logger, "Failed to initialize PxPhysics class. PhysX not initialized" );
				}
				else
				{
					LOG_INFO ( logger, "PxPhysics initialized" );
					physx::PxSceneDesc scene_desc ( px_physics->getTolerancesScale() );
					scene_desc.gravity = PxVec3Converter::toPxVec3(desc.gravity);

					px_cpu_dispatcher = physx::PxDefaultCpuDispatcherCreate ( desc.cpu_threads_count );

					if ( px_cpu_dispatcher == nullptr )
					{
						LOG_ERROR ( logger, "Failed to create CPU dispatcher. PhysX not initialized" );
					}
					else
					{
						LOG_INFO ( logger, "CPU dispatcher initialized" );
						scene_desc.cpuDispatcher = px_cpu_dispatcher;
						scene_desc.filterShader = default_simulation_filter_shader;

						if(desc.enable_hardware)
						{
							physx::PxCudaContextManagerDesc cuda_context_manager_desc;
							px_cuda_context_manager = physx::PxCreateCudaContextManager ( *px_foundation, cuda_context_manager_desc, px_profile_zone_manager );

							if ( px_cuda_context_manager == nullptr )
							{
								LOG_ERROR ( logger, "Failed to create cuda context manager. GPU support is off" );
							}
							else
							{
								px_gpu_dispatcher = px_cuda_context_manager->getGpuDispatcher();
								if (!px_gpu_dispatcher)
								{
									LOG_ERROR(logger, "Failed to get GPU dispatcher. GPU support is off");
								}
								else
								{
									LOG_INFO(logger, "GPU dispatcher initialized");
									scene_desc.gpuDispatcher = px_gpu_dispatcher;
								}
							}
						}
						
						px_scene = px_physics->createScene ( scene_desc );

						if ( px_scene == nullptr )
						{
							LOG_ERROR ( logger, "Failed to create PxScene. PhysX not initialized" );
						}
						else
						{
							LOG_INFO ( logger, "Scene created" );
							is_initialized = true;
						}

					}
				}
			}
			
			if(update_frame_provider) update_frame_provider->addListener(this);
			
		}

		void PhysXSubsystem::shutdown()
		{
			if(update_frame_provider) update_frame_provider->removeListener(this);
			
			if ( px_cuda_context_manager ) px_cuda_context_manager->release();
			if ( px_profile_zone_manager ) px_profile_zone_manager->release();
			if ( px_scene ) px_scene->release();
			if ( px_physics ) px_physics->release();
			if ( px_foundation ) px_foundation->release();
			physx_logger.reset();
		}

		physx::PxPhysics* PhysXSubsystem::getPxPhysics()
		{
			return px_physics;
		}

		physx::PxScene* PhysXSubsystem::getPxScene()
		{
			return px_scene;
		}

		void PhysXSubsystem::onUpdateFrame ( Math::Scalar dt )
		{
			if(px_scene && dt > 0)
			{
				px_scene->simulate(dt);
				px_scene->fetchResults(true);
				
				for(auto &iter : rigid_body_components)
				{
					iter.second->update();
				}
				
			}
		}

		void PhysXSubsystem::addRigidBodyComponent ( const std::string& name, PxRigidBodyComponent* rigid_body_component )
		{
			rigid_body_components[name] = rigid_body_component;
		}

		void PhysXSubsystem::removeRigidBodyComponent ( const std::string& name )
		{
			rigid_body_components.erase(name);
		}
		
		PxRigidBodyComponent* PhysXSubsystem::getRigidBodyComponent(const std::string &name)
		{
			auto iter = rigid_body_components.find(name);
			if (iter == rigid_body_components.end()) {
				LOG_ERROR(logger, "Find request for rigid body component '" + name + "' but it doesn't exist");
				return nullptr;
			}
			return iter->second;
		}

		PhysXSubsystem::~PhysXSubsystem()
		{
		}

	}
}
