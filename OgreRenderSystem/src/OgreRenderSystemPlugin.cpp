#include <stdafx.h>

#include <boost/lexical_cast.hpp>

#include <ComponentSystem/ComponentDesc.h>

#include <Plugins/PluginsManager.h>
#include <OgreRenderSystemPlugin.h>
#include <MessageSystem/MessageDispatcher.h>

#include <Properties/Properties.h>
#include <EngineContext.h>
#include <OgreRenderSubsystem.h>

#include <ComponentSystem/ComponentsManager.h>

#include <Factories/OgreGetDescriptorVisitor.h>

#include <Factories/OgreDataProvidersFactory.h>
#include <Factories/OgreComponentsFactory.h>
#include <Factories/OgreRenderSubsystemFactory.h>

#include <Logging.h>

#include <ComponentSystem/Entity.h>
#include <ComponentSystem/IComponent.h>
#include <ResourceManager/ResourceManager.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderSystemPlugin::OgreRenderSystemPlugin (const char* name) :
		Core::BasePlugin(name)
		{
		}

		OgreRenderSystemPlugin::~OgreRenderSystemPlugin ()
		{
		}

		bool OgreRenderSystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc &desc )
		{
			components_factory.reset(new OgreComponentsFactory());
			data_providers_factory.reset ( new OgreDataProvidersFactory() );
			render_subsystem_factory.reset(new OgreRenderSubsystemFactory(components_factory.get(), data_providers_factory.get()));

			Core::ComponentsManager::getSingleton()->addComponentFactory(render_subsystem_factory.get());
			Core::ComponentsManager::getSingleton()->addComponentFactory(components_factory.get());
			
			Core::ResourceManager::getSingleton()->addDataProviderFactory(data_providers_factory.get());
			
			return true;
		}

		bool OgreRenderSystemPlugin::init ()
		{
			return true;
		}

		bool OgreRenderSystemPlugin::shutdown ()
		{
			return true;
		}

		bool OgreRenderSystemPlugin::uninstall ()
		{
			Core::ComponentsManager::getSingleton()->removeComponentFactory(render_subsystem_factory.get());
			Core::ResourceManager::getSingleton()->removeDataProviderFactory(data_providers_factory.get());
			Core::ComponentsManager::getSingleton()->removeComponentFactory(components_factory.get());

			render_subsystem_factory.reset();
			data_providers_factory.reset ();
			components_factory.reset();
			
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
