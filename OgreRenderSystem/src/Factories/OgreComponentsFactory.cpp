#include <Factories/OgreComponentsFactory.h>
#include <Components/Cameras/OgreCameraComponent.h>
#include <Components/Lights/OgreDirectionalLightComponent.h>
#include <Components/Lights/OgrePointLightComponent.h>
#include <Components/Lights/OgreSpotLightComponent.h>
#include <Components/Renderables/OgreRenderableComponent.h>
#include <Components/VisibilityCheckers/OgreHOQVisibilityChecker.h>
#include <Parsers/Descriptors/OgreRenderableDescriptorParser.h>

#include <Factories/OgreGetDescriptorVisitor.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		static OgreGetDescriptorVisitor<OgreRenderableComponentDescriptor, OgreRenderableDescriptorParser> renderable_descriptor_getter;
		
		OgreComponentsFactory::OgreComponentsFactory():
		render_subsystem(nullptr)
		{
			CreatableObjectDesc creatable_object;
			creatable_object.deleter = std::bind(&OgreComponentsFactory::destroyOgreComponent, this, std::placeholders::_1); 			
			
			creatable_object.creator = std::bind(&OgreComponentsFactory::createCameraComponent, this, std::placeholders::_1);
			creatable_object.type = OgreCameraComponent::getTypeName();
			registerCreator(creatable_object);
			
			creatable_object.creator = std::bind(&OgreComponentsFactory::createDirectionalLightComponent, this, std::placeholders::_1);
			creatable_object.type = OgreDirectionalLightComponent::getTypeName();
			registerCreator(creatable_object);
			
			creatable_object.creator = std::bind(&OgreComponentsFactory::createPointLightComponent, this, std::placeholders::_1);
			creatable_object.type = OgrePointLightComponent::getTypeName();
			registerCreator(creatable_object);
			
			creatable_object.creator = std::bind(&OgreComponentsFactory::createSpotLightComponent, this, std::placeholders::_1);
			creatable_object.type = OgreSpotLightComponent::getTypeName();
			registerCreator(creatable_object);
			
			creatable_object.creator = std::bind(&OgreComponentsFactory::createRenderableComponent, this, std::placeholders::_1);
			creatable_object.type = OgreRenderableComponent::getTypeName();
			registerCreator(creatable_object);
			
			creatable_object.creator = std::bind(&OgreComponentsFactory::createHOQVisibilityChecker, this, std::placeholders::_1);
			creatable_object.type = OgreHOQVisibilityChecker::getTypeName();
			registerCreator(creatable_object);
		}

		void OgreComponentsFactory::setRenderSubsystem ( OgreRenderSubsystem* render_subsystem )
		{
			this->render_subsystem = render_subsystem;
		}
		
		Core::IComponent* OgreComponentsFactory::createCameraComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgreCameraComponentDescriptor descriptor;
			descriptor = boost::get<Core::Properties>(desc.descriptor);
			if(!descriptor.isValid()) return nullptr;
			OgreCameraComponent* camera = new OgreCameraComponent(desc.name.c_str(), descriptor, render_subsystem);
			return camera;
		}

		Core::IComponent* OgreComponentsFactory::createDirectionalLightComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgreDirectionalLightComponentDescriptor descriptor;
			descriptor = boost::get<Core::Properties>(desc.descriptor);
			if(!descriptor.isValid()) return nullptr;
			OgreDirectionalLightComponent* light = new OgreDirectionalLightComponent(desc.name.c_str(), descriptor, render_subsystem);
			return light;
		}

		Core::IComponent* OgreComponentsFactory::createPointLightComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgrePointLightComponentDescriptor descriptor;
			descriptor = boost::get<Core::Properties>(desc.descriptor);
			if(!descriptor.isValid()) return nullptr;
			OgrePointLightComponent* light = new OgrePointLightComponent(desc.name.c_str(), descriptor, render_subsystem);
			return light;
		}

		Core::IComponent* OgreComponentsFactory::createSpotLightComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgreSpotLightComponentDescriptor descriptor;
			descriptor = boost::get<Core::Properties>(desc.descriptor);
			if(!descriptor.isValid()) return nullptr;
			OgreSpotLightComponent* light = new OgreSpotLightComponent(desc.name.c_str(), descriptor, render_subsystem);
			return light;
		}

		Core::IComponent* OgreComponentsFactory::createRenderableComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgreRenderableComponentDescriptor descriptor = desc.descriptor.apply_visitor(renderable_descriptor_getter);
			//descriptor = boost::get<Core::Properties>(desc.descriptor);
			OgreRenderableComponent* renderable = new OgreRenderableComponent(desc.name.c_str(), descriptor, render_subsystem);
			return renderable;
		}

		Core::IComponent* OgreComponentsFactory::createHOQVisibilityChecker ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgreHOQVisibilityCheckerDesc descriptor;
			descriptor = boost::get<Core::Properties>(desc.descriptor);
			if(!descriptor.isValid()) return nullptr;
			OgreHOQVisibilityChecker* visibility_checker = new OgreHOQVisibilityChecker(desc.name.c_str(), descriptor, render_subsystem);
			return visibility_checker;
		}
		
		void OgreComponentsFactory::destroyOgreComponent ( Core::IComponent* component )
		{
			BaseOgreComponent* ogre_component = static_cast<BaseOgreComponent*>(component);
			ogre_component->setDestructionCallback( std::default_delete<Core::IComponent>() );
		}
		
	}
}