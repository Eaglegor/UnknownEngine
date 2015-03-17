#include <stdafx.h>

#include <OgreSynchronizedCEGuiContext.h>
#include <OgreCEGuiContextDesc.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Logging.h>
#include <ICEGuiComponent.h>

namespace UnknownEngine
{
	namespace GUI
	{
		OgreSynchronizedCEGuiContext::OgreSynchronizedCEGuiContext (const char* name, const OgreCEGuiContextDesc &desc):
		OgreCEGuiContext(name, desc)
		{
		}
		
		OgreSynchronizedCEGuiContext::~OgreSynchronizedCEGuiContext()
		{
		}

		bool OgreSynchronizedCEGuiContext::init()
		{
			if(!ogre_render_window) 
			{
				LOG_ERROR(logger, "No OGRE render window provided. Can't create context");
				return false;
			}

			bool success = initializeRenderer();
			if(!success)
			{
				return false;
			}

			ogre_render_window->addListener(this);

			return true;
		}

		void OgreSynchronizedCEGuiContext::shutdown()
		{
			ogre_render_window->removeListener(this);

			shutdownRenderer();
		}

		void OgreSynchronizedCEGuiContext::initComponent(ICEGuiComponent * component) {
			if(component->getState() == ICEGuiComponent::State::INITIALIZATION) component->_init();
		}

		void OgreSynchronizedCEGuiContext::shutdownComponent(ICEGuiComponent * component) {
			if(component->getState() == ICEGuiComponent::State::SHUTTING_DOWN) component->_shutdown();
		}

		void OgreSynchronizedCEGuiContext::destroyComponent(ICEGuiComponent * component) {
			if(component->getState() == ICEGuiComponent::State::DESTRUCTION) component->_destroy();
		}

		void OgreSynchronizedCEGuiContext::onRenderFrame() {
			updateComponents();
		}

	}
}