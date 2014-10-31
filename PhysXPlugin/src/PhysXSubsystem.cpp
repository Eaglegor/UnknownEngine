#include <PhysXSubsystem.h>
#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <LogHelper.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <pxtask/PxCudaContextManager.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <Components/PxRigidBodyComponent.h>

static physx::PxDefaultErrorCallback gDefaultErrorCallback;
static physx::PxDefaultAllocator gDefaultAllocatorCallback;

static physx::PxSimulationFilterShader default_simulation_filter_shader = &physx::PxDefaultSimulationFilterShader;

namespace UnknownEngine
{
	namespace Physics
	{
		PhysXSubsystem::PhysXSubsystem ( Core::EngineContext* engine_context, Core::LogHelper* log_helper ) :
			is_initialized ( false ),
			engine_context ( engine_context ),
			log_helper ( log_helper ),
			px_foundation ( nullptr ),
			px_physics ( nullptr ),
			px_scene ( nullptr ),
			px_cpu_dispatcher ( nullptr ),
			px_gpu_dispatcher ( nullptr ),
			px_cuda_context_manager ( nullptr ),
			px_profile_zone_manager ( nullptr )
		{
		}

		void PhysXSubsystem::init()
		{
			px_foundation = PxCreateFoundation ( PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback );
			if ( px_foundation == nullptr )
			{
				LOG_ERROR ( log_helper, "Failed to create PxFoundation object. PhysX not initialized" );
			}
			else
			{
				LOG_INFO ( log_helper, "PxFoundation initialized" );
				px_physics = PxCreatePhysics ( PX_PHYSICS_VERSION, *px_foundation, physx::PxTolerancesScale() );
				if ( px_physics == nullptr )
				{
					LOG_ERROR ( log_helper, "Failed to initialize PxPhysics class. PhysX not initialized" );
				}
				else
				{
					LOG_INFO ( log_helper, "PxPhysics initialized" );
					physx::PxSceneDesc scene_desc ( px_physics->getTolerancesScale() );
					scene_desc.gravity = physx::PxVec3 ( 0.0f, -0.098f, 0.0f );

					px_cpu_dispatcher = physx::PxDefaultCpuDispatcherCreate ( 2 );

					if ( px_cpu_dispatcher == nullptr )
					{
						LOG_ERROR ( log_helper, "Failed to create CPU dispatcher. PhysX not initialized" );
					}
					else
					{
						LOG_INFO ( log_helper, "CPU dispatcher initialized" );
						scene_desc.cpuDispatcher = px_cpu_dispatcher;
						scene_desc.filterShader = default_simulation_filter_shader;

						px_profile_zone_manager = &physx::PxProfileZoneManager::createProfileZoneManager ( px_foundation );
						if ( px_profile_zone_manager == nullptr )
						{
							LOG_ERROR ( log_helper, "Failed to create PxProfileZoneManager. GPU support is off" );
						}
						else
						{
							physx::PxCudaContextManagerDesc cuda_context_manager_desc;
							px_cuda_context_manager = physx::PxCreateCudaContextManager ( *px_foundation, cuda_context_manager_desc, px_profile_zone_manager );

							if ( px_cuda_context_manager == nullptr )
							{
								LOG_ERROR ( log_helper, "Failed to create cuda context manager. GPU support is off" );
							}
							else
							{
								px_gpu_dispatcher = px_cuda_context_manager->getGpuDispatcher();
								if (!px_gpu_dispatcher)
								{
									LOG_ERROR(log_helper, "Failed to get GPU dispatcher. GPU support is off");
								}
								else
								{
									LOG_INFO(log_helper, "GPU dispatcher initialized");
									scene_desc.gpuDispatcher = px_gpu_dispatcher;
								}
							}
						}

						px_scene = px_physics->createScene ( scene_desc );

						if ( px_scene == nullptr )
						{
							LOG_ERROR ( log_helper, "Failed to create PxScene. PhysX not initialized" );
						}
						else
						{
							LOG_INFO ( log_helper, "Scene created" );
							is_initialized = true;
						}

					}
				}
			}
			
		}

		void PhysXSubsystem::shutdown()
		{
			if ( px_cuda_context_manager ) px_cuda_context_manager->release();
			if ( px_profile_zone_manager ) px_profile_zone_manager->release();
			if ( px_scene ) px_scene->release();
			if ( px_physics ) px_physics->release();
			if ( px_foundation ) px_foundation->release();
		}

		physx::PxPhysics* PhysXSubsystem::getPxPhysics()
		{
			return px_physics;
		}

		physx::PxScene* PhysXSubsystem::getPxScene()
		{
			return px_scene;
		}

		void PhysXSubsystem::onUpdateFrame ( const Core::UpdateFrameMessage& msg )
		{
			if(px_scene && msg.dt > 0)
			{
				px_scene->simulate(msg.dt);
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
				LOG_ERROR(log_helper, "Find request for rigid body component '" + name + "' but it doesn't exist");
				return nullptr;
			}
			return iter->second;
		}

		PhysXSubsystem::~PhysXSubsystem()
		{
		}

	}
}
