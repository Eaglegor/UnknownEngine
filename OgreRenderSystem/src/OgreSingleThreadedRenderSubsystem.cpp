#include <OgreSingleThreadedRenderSubsystem.h>
#include <Components/BaseOgreComponent.h>
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

		bool OgreSingleThreadedRenderSubsystem::init ()
		{
			bool success = UnknownEngine::Graphics::OgreRenderSubsystem::init ();
			if(!success) return false;
			
			if(update_frame_provider) update_frame_provider->addListener(this);
			return true;
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
		
		void OgreSingleThreadedRenderSubsystem::initComponent ( BaseOgreComponent* component )
		{
			if(component->getState() == BaseOgreComponent::State::INITIALIZATION) 
			{
				component->_init();
				components.emplace(component);
			}
		}

		void OgreSingleThreadedRenderSubsystem::shutdownComponent ( BaseOgreComponent* component )
		{
			if(component->getState() == BaseOgreComponent::State::SHUTTING_DOWN) 
			{
				components.erase(component);
				component->_shutdown();
			}
		}

		void OgreSingleThreadedRenderSubsystem::destroyComponent ( BaseOgreComponent* component )
		{
			if(component->getState() == BaseOgreComponent::State::DELETION) component->_destroy();
		}

	}
}