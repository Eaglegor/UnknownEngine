#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <PhysXSubsystemPlugin.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ComponentSystem/ComponentsManager.h>
#include <EngineContext.h>
#include <Logging.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <PhysXSubsystem.h>
#include <Factories/PxShapeDataProvidersFactory.h>
#include <Factories/PxMaterialDataProvidersFactory.h>
#include <Factories/PxRigidBodyComponentsFactory.h>
#include <Factories/PxJointComponentsFactory.h>
#include <Parsers/PhysXSubsystemDescriptorGetter.h>
#include <ResourceManager.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>

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

			PhysXSubsystemDescriptorGetter descriptor_getter;
			this->desc = desc.descriptor.apply_visitor(descriptor_getter);
			this->raw_desc = desc;
			
			logger = CREATE_LOGGER(getName(), this->desc.log_level);
			
			LOG_INFO(logger, "Logger initialized");
			
			LOG_INFO(logger, "Installing PhysX plugin");

			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool PhysXSubsystemPlugin::init () 
		{
			LOG_INFO(logger, "Initializing PhysX plugin");

			physx_subsystem.reset(new PhysXSubsystem(desc, engine_context, logger));
			physx_subsystem->init();
			
			LOG_INFO(logger, "Creating PxShape data providers factory");
			px_shape_data_providers_factory.reset(new PxShapeDataProvidersFactory(physx_subsystem.get()));

			LOG_INFO(logger, "Registering PxShape data providers factory");
			engine_context->getResourceManager()->addDataProviderFactory(px_shape_data_providers_factory.get());
			
			LOG_INFO(logger, "Creating PxMaterial data providers factory");
			px_material_data_providers_factory.reset(new PxMaterialDataProvidersFactory(physx_subsystem.get()));
			
			LOG_INFO(logger, "Registering PxMaterial data providers factory");
			engine_context->getResourceManager()->addDataProviderFactory(px_material_data_providers_factory.get());

			LOG_INFO(logger, "Creating PxRigidBody components factory");
			px_rigid_body_components_factory.reset(new PxRigidBodyComponentsFactory(physx_subsystem.get(), engine_context));

			LOG_INFO(logger, "Registering PxRigidBody components factory");
			engine_context->getComponentsManager()->addComponentFactory(px_rigid_body_components_factory.get());

			LOG_INFO(logger, "Creating PxJoint components factory");
			px_joint_components_factory.reset(new PxJointComponentsFactory(physx_subsystem.get(), engine_context));

			LOG_INFO(logger, "Registering PxJoint components factory");
			engine_context->getComponentsManager()->addComponentFactory(px_joint_components_factory.get());

			listener.reset(new Core::BaseMessageListener(getName(), engine_context));
			{
				typedef Core::UpdateFrameMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
				
				listener->createMessageBuffer<MessageType, BufferType>(physx_subsystem.get(), &PhysXSubsystem::onUpdateFrame);
			}
			
			listener->registerAtDispatcher();
			
			return true;
		}

		bool PhysXSubsystemPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down PhysX plugin");

			listener->unregisterAtDispatcher();
			
			LOG_INFO(logger, "Unregistering PxJoint components factory");
			engine_context->getComponentsManager()->removeComponentFactory(px_joint_components_factory.get());

			LOG_INFO(logger, "Destroying PxJoint components factory");
			px_joint_components_factory.reset();

			LOG_INFO(logger, "Unregistering PxRigidBody components factory");
			engine_context->getComponentsManager()->removeComponentFactory(px_rigid_body_components_factory.get());

			LOG_INFO(logger, "Destroying PxRigidBody components factory");
			px_rigid_body_components_factory.reset();

			LOG_INFO(logger, "Unregistering PxMaterial data providers factory");
			engine_context->getResourceManager()->removeDataProviderFactory(px_material_data_providers_factory.get());

			LOG_INFO(logger, "Destroying PxMaterial data providers factory");
			px_material_data_providers_factory.reset();
			
			LOG_INFO(logger, "Unregistering PxShape data providers factory");
			engine_context->getResourceManager()->removeDataProviderFactory(px_shape_data_providers_factory.get());

			LOG_INFO(logger, "Destroying PxShape data providers factory");
			px_shape_data_providers_factory.reset();

			physx_subsystem->shutdown();
			physx_subsystem.reset();

			return true;
		}

		bool PhysXSubsystemPlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling PhysX plugin");
		  
			RELEASE_LOGGER(logger);
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
