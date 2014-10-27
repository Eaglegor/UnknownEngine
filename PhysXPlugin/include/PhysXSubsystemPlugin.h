#pragma once

#include <InlineSpecification.h>
#include <Plugins/Plugin.h>
#include <SubsystemDesc.h>
#include <memory>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
		class LogHelper;
	}

	namespace Physics
	{

		class PhysXSubsystem;
		class PxShapeDataProvidersFactory;
		class PxMaterialDataProvidersFactory;
		class PxRigidBodyComponentsFactory;

		class PhysXSubsystemPlugin: public Core::Plugin
		{
			public:
				PhysXSubsystemPlugin();
				virtual ~PhysXSubsystemPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				std::unique_ptr<Core::LogHelper> log_helper;
				std::unique_ptr<PhysXSubsystem> physx_subsystem;

				std::unique_ptr<PxShapeDataProvidersFactory> px_shape_data_providers_factory;
				std::unique_ptr<PxMaterialDataProvidersFactory> px_material_data_providers_factory;
				std::unique_ptr<PxRigidBodyComponentsFactory> px_rigid_body_components_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
