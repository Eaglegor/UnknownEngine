#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <PhysXSubsystemPlugin.h>
#include <MessageSystem/MessageDictionary.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <PhysXSubsystem.h>
#include <Factories/PxShapeDataProvidersFactory.h>
#include <Factories/PxMaterialDataProvidersFactory.h>
#include <ResourceManager.h>

namespace UnknownEngine
{
	namespace Physics
	{

		PhysXSubsystemPlugin::PhysXSubsystemPlugin ()
		{
		}

		PhysXSubsystemPlugin::~PhysXSubsystemPlugin ()
		{
		}

		bool PhysXSubsystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			log_helper.reset(new Core::LogHelper(getName(), Core::LogMessage::Severity::LOG_SEVERITY_INFO, plugins_manager->getEngineContext()));
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing PhysX plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool PhysXSubsystemPlugin::init () 
		{
			LOG_INFO(log_helper, "Initializing PhysX plugin");

			physx_subsystem.reset(new PhysXSubsystem(engine_context, log_helper.get()));

			LOG_INFO(log_helper, "Creating PxShape data providers factory");
			px_shape_data_providers_factory.reset(new PxShapeDataProvidersFactory(physx_subsystem.get()));

			LOG_INFO(log_helper, "Registering PxShape data providers factory");
			engine_context->getResourceManager()->addDataProviderFactory(px_shape_data_providers_factory.get());
			
			LOG_INFO(log_helper, "Creating PxMaterial data providers factory");
			px_material_data_providers_factory.reset(new PxMaterialDataProvidersFactory(physx_subsystem.get()));
			
			LOG_INFO(log_helper, "Registering PxMaterial data providers factory");
			engine_context->getResourceManager()->addDataProviderFactory(px_material_data_providers_factory.get());

			return true;
		}

		bool PhysXSubsystemPlugin::shutdown () 
		{
			LOG_INFO(log_helper, "Shutting down PhysX plugin");
		  
			LOG_INFO(log_helper, "Unregistering PxMaterial data providers factory");
			engine_context->getResourceManager()->removeDataProviderFactory(px_material_data_providers_factory.get());

			LOG_INFO(log_helper, "Destroying PxMaterial data providers factory");
			px_material_data_providers_factory.reset();
			
			LOG_INFO(log_helper, "Unregistering PxShape data providers factory");
			engine_context->getResourceManager()->removeDataProviderFactory(px_shape_data_providers_factory.get());

			LOG_INFO(log_helper, "Destroying PxShape data providers factory");
			px_shape_data_providers_factory.reset();

			physx_subsystem.reset();

			return true;
		}

		bool PhysXSubsystemPlugin::uninstall () 
		{
			LOG_INFO(log_helper, "Uninstalling PhysX plugin");
		  
			log_helper.reset();
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
