#pragma once

#include <OGRE/OgreRenderWindow.h>
#include <OgreRenderSubsystem.h>
#include <Descriptors/OgreRenderWindowDescriptor.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreRenderWindowWrapper
		{
		public:
			OgreRenderWindowWrapper(OgreRenderSubsystem* render_subsystem, OgreRenderWindowDescriptor& desc);
			virtual ~OgreRenderWindowWrapper();
			
			UNKNOWNENGINE_INLINE
			void setVisible(bool visible)
			{
				render_window->setVisible(visible);
			}
			
			UNKNOWNENGINE_INLINE
			Ogre::RenderWindow* getOgreRenderWindow()
			{
				return render_window;
			}
			
		private:
			OgreRenderSubsystem* render_subsystem;
			Ogre::RenderWindow *render_window;
		};
	}
}