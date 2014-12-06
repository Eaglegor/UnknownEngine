#include <stdafx.h>

#include <Factories/OgreRenderableComponentsFactory.h>

#include <Components/Renderables/OgreRenderableComponent.h>
#include <Parsers/Descriptors/OgreRenderableDescriptorParser.h>

#include <Factories/DefaultComponentCreatorFunc.h>

#include <Factories/OgreGetDescriptorVisitor.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static OgreGetDescriptorVisitor<OgreRenderableComponentDescriptor, OgreRenderableDescriptorParser> renderable_descriptor_getter;
		
		OgreRenderableComponentsFactory::OgreRenderableComponentsFactory ( OgreRenderSubsystem* render_system, Core::EngineContext* engine_context, Core::ILogger* logger ):
		BaseOgreComponentFactory(render_system, engine_context, logger)
		{
			CreatableObjectDesc creatable_component;
			creatable_component.type = OGRE_RENDERABLE_COMPONENT_TYPE;
			creatable_component.creator = getDefaultCreator<OgreRenderableComponent>(renderable_descriptor_getter, render_system, engine_context);
			registerCreator(creatable_component);
		}

		const char* OgreRenderableComponentsFactory::getName() const
		{
			return "Graphics.OgreRenderSubsystem.RenderableComponentsFactory";
		}

	} // namespace Graphics
} // namespace UnknownEngine
