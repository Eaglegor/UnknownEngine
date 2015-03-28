#include <Factories/OgreRenderSubsystemFactory.h>
#include <OgreSingleThreadedRenderSubsystem.h>
#include <OgreSeparateThreadRenderSubsystem.h>
#include <Descriptors/OgreSeparateThreadRenderSubsystemDescriptor.h>
#include <OgreRenderWindowComponent.h>
#include <Factories/OgreGetDescriptorVisitor.h>
#include <Factories/OgreComponentsFactory.h>
#include <Factories/OgreDataProvidersFactory.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		typedef OgreSingleThreadedRenderSubsystemDescriptor STDescriptor;
		typedef OgreSeparateThreadRenderSubsystemDescriptor MTDescriptor;
		typedef OgreRenderWindowDescriptor WindowDescriptor;
		
		OgreRenderSubsystemFactory::OgreRenderSubsystemFactory ( OgreComponentsFactory* components_factory, OgreDataProvidersFactory* data_providers_factory ):
		render_subsystem(nullptr),
		components_factory(components_factory),
		data_providers_factory(data_providers_factory)
		{
			CreatableObjectDesc creatable_object;
			creatable_object.type = OgreSingleThreadedRenderSubsystem::getTypeName();
			creatable_object.creator = std::bind(&OgreRenderSubsystemFactory::createSingleThreadedOgreRenderSubsystem, this, std::placeholders::_1);
			creatable_object.deleter = std::bind(&OgreRenderSubsystemFactory::destroyRenderSubsystem, this, std::placeholders::_1);
			registerCreator(creatable_object);
			
			creatable_object.type = OgreSeparateThreadRenderSubsystem::getTypeName();
			creatable_object.creator = std::bind(&OgreRenderSubsystemFactory::createSeparateThreadOgreRenderSubsystem, this, std::placeholders::_1);
			registerCreator(creatable_object);
			
			creatable_object.type = OgreRenderWindowComponent::getTypeName();
			creatable_object.creator = std::bind(&OgreRenderSubsystemFactory::createOgreRenderWindow, this, std::placeholders::_1);
			creatable_object.deleter = std::bind(&OgreRenderSubsystemFactory::destroyOgreRenderWindow, this, std::placeholders::_1);
			registerCreator(creatable_object);
		}

		Core::IComponent* OgreRenderSubsystemFactory::createSingleThreadedOgreRenderSubsystem ( const Core::ComponentDesc& desc )
		{
			if(render_subsystem) return nullptr;
			STDescriptor cdesc;
			cdesc = boost::get<Core::Properties>(desc.descriptor);
			if(!cdesc.isValid()) return nullptr;
			render_subsystem = new OgreSingleThreadedRenderSubsystem(desc.name.c_str(), cdesc);
			components_factory->setRenderSubsystem(render_subsystem);
			data_providers_factory->setRenderSubsystem(render_subsystem);
			return render_subsystem;
		}

		Core::IComponent* OgreRenderSubsystemFactory::createSeparateThreadOgreRenderSubsystem ( const Core::ComponentDesc& desc )
		{
			if(render_subsystem) return nullptr;
			MTDescriptor cdesc;
			cdesc = boost::get<Core::Properties>(desc.descriptor); 
			if(!cdesc.isValid()) return nullptr;
			render_subsystem = new OgreSeparateThreadRenderSubsystem(desc.name.c_str(), cdesc);
			components_factory->setRenderSubsystem(render_subsystem);
			data_providers_factory->setRenderSubsystem(render_subsystem);
			return render_subsystem;
		}

		void OgreRenderSubsystemFactory::destroyRenderSubsystem ( Core::IComponent* component )
		{
			components_factory->setRenderSubsystem(nullptr);
			data_providers_factory->setRenderSubsystem(nullptr);
			delete component;
		}
	
		Core::IComponent* OgreRenderSubsystemFactory::createOgreRenderWindow ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			WindowDescriptor cdesc;
			cdesc = boost::get<Core::Properties>(desc.descriptor);
			if(!cdesc.isValid()) return nullptr;
			OgreRenderWindowComponent* window = new OgreRenderWindowComponent(desc.name.c_str(), cdesc, render_subsystem);
			return window;
		}

		void OgreRenderSubsystemFactory::destroyOgreRenderWindow ( Core::IComponent* component )
		{
			BaseOgreComponent* ogre_component = static_cast<BaseOgreComponent*>(component);
			ogre_component->setDestructionCallback(std::default_delete<Core::IComponent>());
		}
		
	}
}