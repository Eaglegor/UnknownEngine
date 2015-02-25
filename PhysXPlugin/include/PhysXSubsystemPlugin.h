#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include "Descriptors/PhysXSubsystemDesc.h"
#include <memory>

namespace UnknownEngine
{
	namespace Physics
	{
		class PxComponentsFactory;
		class PxDataProvidersFactory;
		class PxSubsystemFactory;

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
				std::unique_ptr<PxComponentsFactory> px_components_factory;
				std::unique_ptr<PxDataProvidersFactory> px_data_providers_factory;
				std::unique_ptr<PxSubsystemFactory> px_subsystem_factory;
				
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
