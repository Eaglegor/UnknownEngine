#include <Factories/OgreComponentsFactory.h>
#include <Components/Cameras/OgreCameraComponent.h>
#include <Components/Lights/OgreDirectionalLightComponent.h>
#include <Components/Lights/OgrePointLightComponent.h>
#include <Components/Lights/OgreSpotLightComponent.h>
#include <Components/Renderables/OgreRenderableComponent.h>
#include <Parsers/Descriptors/OgreCameraDescriptorParser.h>
#include <Parsers/Descriptors/OgreRenderableDescriptorParser.h>
#include <Parsers/Descriptors/OgrePointLightDescriptorParser.h>
#include <Parsers/Descriptors/OgreDirectionalLightDescriptorParser.h>
#include <Parsers/Descriptors/OgreSpotLightDescriptorParser.h>

#include <Factories/OgreGetDescriptorVisitor.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		static OgreGetDescriptorVisitor<OgreCameraComponentDescriptor, OgreCameraDescriptorParser> camera_descriptor_getter;
		static OgreGetDescriptorVisitor<OgreRenderableComponentDescriptor, OgreRenderableDescriptorParser> renderable_descriptor_getter;
		static OgreGetDescriptorVisitor<OgrePointLightComponentDescriptor, OgrePointLightDescriptorParser> point_light_descriptor_getter;
		static OgreGetDescriptorVisitor<OgreDirectionalLightComponentDescriptor, OgreDirectionalLightDescriptorParser> directional_light_descriptor_getter;
		static OgreGetDescriptorVisitor<OgreSpotLightComponentDescriptor, OgreSpotLightDescriptorParser> spot_light_descriptor_getter;
		
		OgreComponentsFactory::OgreComponentsFactory():
		render_subsystem(nullptr)
		{
			CreatableObjectDesc creatable_object;
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
		}

		void OgreComponentsFactory::setRenderSubsystem ( OgreRenderSubsystem* render_subsystem )
		{
			this->render_subsystem = render_subsystem;
		}
		
		Core::IComponent* OgreComponentsFactory::createCameraComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgreCameraComponentDescriptor descriptor = desc.descriptor.apply_visitor(camera_descriptor_getter);
			OgreCameraComponent* camera = new OgreCameraComponent(desc.name.c_str(), descriptor, render_subsystem);
			return camera;
		}

		Core::IComponent* OgreComponentsFactory::createDirectionalLightComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgreDirectionalLightComponentDescriptor descriptor = desc.descriptor.apply_visitor(directional_light_descriptor_getter);
			OgreDirectionalLightComponent* light = new OgreDirectionalLightComponent(desc.name.c_str(), descriptor, render_subsystem);
			return light;
		}

		Core::IComponent* OgreComponentsFactory::createPointLightComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgrePointLightComponentDescriptor descriptor = desc.descriptor.apply_visitor(point_light_descriptor_getter);
			OgrePointLightComponent* light = new OgrePointLightComponent(desc.name.c_str(), descriptor, render_subsystem);
			return light;
		}

		Core::IComponent* OgreComponentsFactory::createSpotLightComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgreSpotLightComponentDescriptor descriptor = desc.descriptor.apply_visitor(spot_light_descriptor_getter);
			OgreSpotLightComponent* light = new OgreSpotLightComponent(desc.name.c_str(), descriptor, render_subsystem);
			return light;
		}

		Core::IComponent* OgreComponentsFactory::createRenderableComponent ( const Core::ComponentDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			OgreRenderableComponentDescriptor descriptor = desc.descriptor.apply_visitor(renderable_descriptor_getter);
			OgreRenderableComponent* renderable = new OgreRenderableComponent(desc.name.c_str(), descriptor, render_subsystem);
			return renderable;
		}

		void OgreComponentsFactory::destroyOgreComponent ( Core::IComponent* component )
		{
			BaseOgreComponent* ogre_component = static_cast<BaseOgreComponent*>(component);
			ogre_component->setDestructionCallback( std::default_delete<Core::IComponent>() );
		}
		
	}
}