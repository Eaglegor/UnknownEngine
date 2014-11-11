#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <PhysXSubsystemPlugin.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ComponentsManager.h>
#include <EngineContext.h>
#include <LogHelper.h>
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
			
			log_helper.reset(new Utils::LogHelper(getName(), this->desc.log_level, plugins_manager->getEngineContext()));
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing PhysX plugin");

			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool PhysXSubsystemPlugin::init () 
		{
			LOG_INFO(log_helper, "Initializing PhysX plugin");

			physx_subsystem.reset(new PhysXSubsystem(desc, engine_context, log_helper.get()));
			physx_subsystem->init();
			
			LOG_INFO(log_helper, "Creating PxShape data providers factory");
			px_shape_data_providers_factory.reset(new PxShapeDataProvidersFactory(physx_subsystem.get()));

			LOG_INFO(log_helper, "Registering PxShape data providers factory");
			engine_context->getResourceManager()->addDataProviderFactory(px_shape_data_providers_factory.get());
			
			LOG_INFO(log_helper, "Creating PxMaterial data providers factory");
			px_material_data_providers_factory.reset(new PxMaterialDataProvidersFactory(physx_subsystem.get()));
			
			LOG_INFO(log_helper, "Registering PxMaterial data providers factory");
			engine_context->getResourceManager()->addDataProviderFactory(px_material_data_providers_factory.get());

			LOG_INFO(log_helper, "Creating PxRigidBody components factory");
			px_rigid_body_components_factory.reset(new PxRigidBodyComponentsFactory(physx_subsystem.get(), engine_context));

			LOG_INFO(log_helper, "Registering PxRigidBody components factory");
			engine_context->getComponentsManager()->addComponentFactory(px_rigid_body_components_factory.get());

			LOG_INFO(log_helper, "Creating PxJoint components factory");
			px_joint_components_factory.reset(new PxJointComponentsFactory(physx_subsystem.get(), engine_context));

			LOG_INFO(log_helper, "Registering PxJoint components factory");
			engine_context->getComponentsManager()->addComponentFactory(px_joint_components_factory.get());

			listener.reset(new Core::BaseMessageListener(getName(), engine_context));
			listener->registerSupportedMessageTypes(raw_desc.received_messages);
			
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
			LOG_INFO(log_helper, "Shutting down PhysX plugin");

			listener->unregisterAtDispatcher();
			
			LOG_INFO(log_helper, "Unregistering PxJoint components factory");
			engine_context->getComponentsManager()->removeComponentFactory(px_joint_components_factory.get());

			LOG_INFO(log_helper, "Destroying PxJoint components factory");
			px_joint_components_factory.reset();

			LOG_INFO(log_helper, "Unregistering PxRigidBody components factory");
			engine_context->getComponentsManager()->removeComponentFactory(px_rigid_body_components_factory.get());

			LOG_INFO(log_helper, "Destroying PxRigidBody components factory");
			px_rigid_body_components_factory.reset();

			LOG_INFO(log_helper, "Unregistering PxMaterial data providers factory");
			engine_context->getResourceManager()->removeDataProviderFactory(px_material_data_providers_factory.get());

			LOG_INFO(log_helper, "Destroying PxMaterial data providers factory");
			px_material_data_providers_factory.reset();
			
			LOG_INFO(log_helper, "Unregistering PxShape data providers factory");
			engine_context->getResourceManager()->removeDataProviderFactory(px_shape_data_providers_factory.get());

			LOG_INFO(log_helper, "Destroying PxShape data providers factory");
			px_shape_data_providers_factory.reset();

			physx_subsystem->shutdown();
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
