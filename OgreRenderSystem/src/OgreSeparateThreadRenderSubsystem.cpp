#include <OgreSeparateThreadRenderSubsystem.h>
#include <Descriptors/OgreSeparateThreadRenderSubsystemDescriptor.h>
#include <OgreRenderFrameListener.h>
#include <OGRE/OgreRoot.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreSeparateThreadRenderSubsystem::OgreSeparateThreadRenderSubsystem ( const char* name, const OgreSeparateThreadRenderSubsystemDescriptor& desc ):
		OgreRenderSubsystem ( name, desc.base_descriptor )
		{
		}

		OgreSeparateThreadRenderSubsystem::~OgreSeparateThreadRenderSubsystem()
		{
		}
		
		void OgreSeparateThreadRenderSubsystem::init ( const Core::IEntity* parent_entity )
		{
			listener.reset(new OgreRenderFrameListener(this));
			
			rendering_thread.reset(new std::thread( [this, parent_entity]()
			{
				this->OgreRenderSubsystem::init ( parent_entity );

				this->getRoot()->addFrameListener(listener.get());
				this->getRoot()->startRendering();
				this->getRoot()->removeFrameListener( listener.get() );
				
				this->OgreRenderSubsystem::shutdown();
				listener->setFinished();
			}
			));
		}

		void OgreSeparateThreadRenderSubsystem::shutdown()
		{
			listener->stopRendering();
			listener->waitUntilFinished();
			listener.reset();
		}
		
	}
}