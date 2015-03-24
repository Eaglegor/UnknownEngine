#include <stdafx.h>

#include <OgreCEGuiContext.h>
#include <OgreCEGuiContextDesc.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/System.h>
#include <CEGUI/GUIContext.h>
#include <CEGUI/Window.h>
#include <Logging.h>
#include <Scalar.h>
#include <ScanCodeConverter.h>

namespace UnknownEngine
{
	namespace GUI
	{
		OgreCEGuiContext::OgreCEGuiContext ( const char* name, const OgreCEGuiContextDesc &desc ) :
			Core::BaseComponent ( name ),
			renderer ( nullptr ),
			main_window(nullptr),
			logger ( name, desc.log_level ),
			ogre_render_window ( desc.render_window ),
			keyboard_handler(desc.keyboard_handler),
			mouse_handler(desc.mouse_handler)
		{
		}

		OgreCEGuiContext::~OgreCEGuiContext()
		{
		}

		bool OgreCEGuiContext::initializeRenderer()
		{
			LOG_INFO ( logger, "Initializing CEGUI Ogre context" );
			renderer = &CEGUI::OgreRenderer::bootstrapSystem ( *ogre_render_window->getOgreRenderWindow() );
			
			if ( !renderer )
			{
				LOG_ERROR ( logger, "Failed to initialize CEGUI Ogre context" );
				return false;
			}

			main_window = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", std::string(getName()) + ".MainWindow");
			if(!main_window)
			{
				LOG_ERROR ( logger, "Failed to create CEGUI main window" );
				CEGUI::OgreRenderer::destroySystem();
				return false;
			}
			
			CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(main_window);
			
			CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
			
			LOG_INFO ( logger, "CEGUI Ogre context created" );
			
			if(keyboard_handler) keyboard_handler->addKeyboardEventsListener(this);
			if(mouse_handler) mouse_handler->addMouseEventsListener(this);
			
			//CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
			
			return true;
		}

		void OgreCEGuiContext::shutdownRenderer()
		{
			
			if(mouse_handler) mouse_handler->removeMouseEventsListener(this);
			if(keyboard_handler) keyboard_handler->removeKeyboardEventsListener(this);
			
			if(main_window)
			{
				LOG_INFO(logger, "Destroying CEGUI main window");
				
				CEGUI::WindowManager::getSingleton().destroyWindow(main_window);
				
				main_window = nullptr;
				LOG_INFO(logger, "CEGUI main window destroyed");
			}
			if(renderer) 
			{
				LOG_INFO(logger, "Destroying CEGUI Ogre context");

				CEGUI::OgreRenderer::destroySystem();
				renderer = nullptr;
				LOG_INFO(logger, "CEGUI Ogre context destroyed");
			}
		}

		CEGUI::Window* OgreCEGuiContext::getCEGuiWindow()
		{
			return main_window;
		}

		void OgreCEGuiContext::addChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			main_window->addChild(child->getCEGuiWindow());
		}

		void OgreCEGuiContext::removeChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			main_window->removeChild(child->getCEGuiWindow()->getID());
		}

		void OgreCEGuiContext::onKeyboardEvent ( const IO::KeyboardEvent& evt )
		{
			switch(evt.new_state)
			{
				case IO::KeyState::KEY_PRESSED:
				{
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(ScanCodeConverter::toCeguiScancode(evt.key));
					CEGUI::System::getSingleton().getDefaultGUIContext().injectChar (evt.character);
					break;
				}
				case IO::KeyState::KEY_UNPRESSED:
				{
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(ScanCodeConverter::toCeguiScancode(evt.key));
					break;
				}
			}
		}

		void OgreCEGuiContext::onMouseButtonEvent ( const IO::MouseButtonEvent& evt )
		{
			switch(evt.new_state)
			{
				case IO::MouseButtonState::MOUSE_BUTTON_PRESSED:
				{
					switch(evt.button_id)
					{
						case 0:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
							break;
						}
						case 1:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::RightButton);
							break;
						}
						case 2:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MiddleButton);
							break;
						}
						case 3:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::X1Button);
							break;
						}
						case 4:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::X2Button);
							break;
						}
						default:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::NoButton);
							break;
						}
					}
					
				}
				case IO::MouseButtonState::MOUSE_BUTTON_UNPRESSED:
				{
					switch(evt.button_id)
					{
						case 0:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton);
							break;
						}
						case 1:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::RightButton);
							break;
						}
						case 2:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MiddleButton);
							break;
						}
						case 3:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::X1Button);
							break;
						}
						case 4:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::X2Button);
							break;
						}
						default:
						{
							CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::NoButton);
							break;
						}
					}
				}
			}
		}

		void OgreCEGuiContext::onMouseMoveEvent ( const IO::MouseMovedEvent& evt )
		{
			if(evt.new_x != 0 || evt.new_y != 0)
			{
				CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(evt.new_x, evt.new_y);
			}
			else
			{
				CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(evt.delta_x, evt.delta_y);
			}
		}

		void OgreCEGuiContext::onMouseWheelEvent ( const IO::MouseWheelEvent& evt )
		{
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(evt.delta);
		}
		
		Core::IComponentInterface* OgreCEGuiContext::getInterface ( const Core::ComponentType& type )
		{
			using namespace ComponentInterfaces; 
			if(type == CEGuiWidgetComponent::getType()) return static_cast<CEGuiWidgetComponent*>(this);
			if(type == CEGuiContextComponent::getType()) return static_cast<CEGuiContextComponent*>(this);
			return nullptr;
		}

		void OgreCEGuiContext::updateComponents()
		{
			for(ICEGuiComponent* component : components)
			{
				if(component->getState() == ICEGuiComponent::State::WORK) component->_update();
			}
		}

	}
}
