#include <stdafx.h>

#include <Factories/OgreCameraComponentsFactory.h>

#include <Components/Cameras/OgreCameraComponent.h>
#include <Parsers/Descriptors/OgreCameraDescriptorParser.h>

#include <Factories/DefaultComponentCreatorFunc.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreCameraComponentsFactory::OgreCameraComponentsFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ):
		BaseOgreComponentFactory(render_subsystem, engine_context, log_helper)
		{
			
			CreatableObjectDesc creatable_component;
			creatable_component.type = OGRE_CAMERA_COMPONENT_TYPE;
			creatable_component.creator = getDefaultCreator<OgreCameraComponent, OgreCameraComponentDescriptor, OgreCameraDescriptorParser>(render_subsystem, engine_context);
			registerCreator(creatable_component);
			
		}

		const char* OgreCameraComponentsFactory::getName()
		{
			return "Graphics.OgreRenderSubsystem.CameraComponentsFactory";
		}

	} // namespace Graphics
} // namespace UnknownEngine
