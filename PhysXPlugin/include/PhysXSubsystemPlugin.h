#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include "Descriptors/PhysXSubsystemDesc.h"
#include <memory>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
		class BaseMessageListener;
		class ILogger;
	}

	namespace Physics
	{

		class PhysXSubsystem;
		class PxShapeDataProvidersFactory;
		class PxMaterialDataProvidersFactory;
		class PxRigidBodyComponentsFactory;
		class PxJointComponentsFactory;

		class PhysXSubsystemPlugin: public Core::BasePlugin
		{
			public:
				PhysXSubsystemPlugin(const char* name);
				virtual ~PhysXSubsystemPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				PhysXSubsystemDesc desc;
				Core::SubsystemDesc raw_desc;
				Core::EngineContext* engine_context;
				Core::ILogger* logger;
				std::unique_ptr<PhysXSubsystem> physx_subsystem;

				std::unique_ptr<PxShapeDataProvidersFactory> px_shape_data_providers_factory;
				std::unique_ptr<PxMaterialDataProvidersFactory> px_material_data_providers_factory;
				std::unique_ptr<PxRigidBodyComponentsFactory> px_rigid_body_components_factory;
				std::unique_ptr<PxJointComponentsFactory> px_joint_components_factory;
				
				std::unique_ptr<Core::BaseMessageListener> listener;
				
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
