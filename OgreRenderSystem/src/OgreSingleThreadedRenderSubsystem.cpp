#include <OgreSingleThreadedRenderSubsystem.h>
#include <OgreWindowEventUtilities.h>
#include <OgreRoot.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		OgreSingleThreadedRenderSubsystem::OgreSingleThreadedRenderSubsystem ( const char* name, const OgreSingleThreadedRenderSubsystemDescriptor& desc ):
		OgreRenderSubsystem ( name, desc.base_descriptor ),
		update_frame_provider(desc.update_frame_provider)
		{
			
		}

		void OgreSingleThreadedRenderSubsystem::init ( const Core::IEntity* parent_entity )
		{
			UnknownEngine::Graphics::OgreRenderSubsystem::init ( parent_entity );
			
			if(update_frame_provider) update_frame_provider->addListener(this);
		}

		void OgreSingleThreadedRenderSubsystem::shutdown()
		{
			if(update_frame_provider) update_frame_provider->removeListener(this);
			
			UnknownEngine::Graphics::OgreRenderSubsystem::shutdown();
		}
		
		void OgreSingleThreadedRenderSubsystem::onUpdateFrame ( Math::Scalar dt )
		{
			UnknownEngine::Graphics::OgreRenderSubsystem::onUpdateFrame ( dt );
			Ogre::WindowEventUtilities::messagePump();
			getRoot()->renderOneFrame();
		}

	}
}