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
		
		OgreRenderableComponentsFactory::OgreRenderableComponentsFactory ( OgreRenderSubsystem* render_system, Core::EngineContext* engine_context, Core::LogHelper* log_helper ):
		BaseOgreComponentFactory(render_system, engine_context, log_helper)
		{
			CreatableObjectDesc creatable_component;
			creatable_component.type = OGRE_RENDERABLE_COMPONENT_TYPE;
			creatable_component.creator = getDefaultCreator<OgreRenderableComponent>(renderable_descriptor_getter, render_system, engine_context);
			registerCreator(creatable_component);
		}

		const char* OgreRenderableComponentsFactory::getName()
		{
			return "Graphics.OgreRenderSubsystem.RenderableComponentsFactory";
		}

	} // namespace Graphics
} // namespace UnknownEngine
