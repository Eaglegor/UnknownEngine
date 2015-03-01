#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <PhysXSubsystemPlugin.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ComponentSystem/ComponentsManager.h>
#include <EngineContext.h>
#include <Logging.h>
#include <PhysXSubsystem.h>
#include <Factories/PxDataProvidersFactory.h>
#include <Factories/PxComponentsFactory.h>
#include <Factories/PxSubsystemFactory.h>
#include <Parsers/PhysXSubsystemDescriptorGetter.h>
#include <ResourceManager/ResourceManager.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		PhysXSubsystemPlugin::PhysXSubsystemPlugin ( const char* name ):
		Core::BasePlugin(name)
		{
		}

		PhysXSubsystemPlugin::~PhysXSubsystemPlugin ()
		{
		}

		bool PhysXSubsystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
			px_components_factory.reset(new PxComponentsFactory());
			px_data_providers_factory.reset(new PxDataProvidersFactory());
			px_subsystem_factory.reset(new PxSubsystemFactory(px_components_factory.get(), px_data_providers_factory.get()));
			
			Core::ComponentsManager::getSingleton()->addComponentFactory(px_components_factory.get());
			Core::ResourceManager::getSingleton()->addDataProviderFactory(px_data_providers_factory.get());
			Core::ComponentsManager::getSingleton()->addComponentFactory(px_subsystem_factory.get());
			
			return true;
		}

		bool PhysXSubsystemPlugin::init () 
		{
			return true;
		}

		bool PhysXSubsystemPlugin::shutdown () 
		{
			return true;
		}

		bool PhysXSubsystemPlugin::uninstall () 
		{
			Core::ComponentsManager::getSingleton()->removeComponentFactory(px_subsystem_factory.get());
			Core::ResourceManager::getSingleton()->removeDataProviderFactory(px_data_providers_factory.get());
			Core::ComponentsManager::getSingleton()->removeComponentFactory(px_components_factory.get());
			
			px_subsystem_factory.reset(new PxSubsystemFactory(px_components_factory.get(), px_data_providers_factory.get()));
			px_data_providers_factory.reset(new PxDataProvidersFactory());
			px_components_factory.reset(new PxComponentsFactory());
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
