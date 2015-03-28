#include <FrameWindowComponent.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/WindowManager.h>

namespace UnknownEngine
{
	namespace GUI
	{
		FrameWindowComponent::FrameWindowComponent(const char* name, const FrameWindowDesc &desc, Core::IComponent* context) : 
		BaseCEGuiComponent(name, context),
		desc(desc),
		window(nullptr),
		parent_widget(desc.parent_window),
		logger(name, desc.log_level),
		fps_counter(2500, std::bind(&FrameWindowComponent::updateFps, this, std::placeholders::_1))
		{
		}

		FrameWindowComponent::~FrameWindowComponent()
		{
		}
		
		void FrameWindowComponent::internalInit()
		{
			if(!parent_widget)
			{
				LOG_ERROR(logger, "No parent window provided. Can't create component");
				return;
			}
			
			CEGUI::WindowManager& mgr = CEGUI::WindowManager::getSingleton();
			window = static_cast<CEGUI::FrameWindow*>( mgr.createWindow(desc.window_type.c_str(), getName()) );
			
			if(!window)
			{
				LOG_ERROR(logger, "Failed to initialize frame window");
				return;
			}
			
			window->setText(desc.window_caption.c_str());
			
			parent_widget->addChild(this);
			
		}

		void FrameWindowComponent::internalShutdown()
		{
			if(window)
			{
				parent_widget->removeChild(this);
				
				LOG_INFO(logger, "Destroying frame window");
				CEGUI::WindowManager::getSingleton().destroyWindow(window);
				LOG_INFO(logger, "Frame window destroyed");
			}
		}

		CEGUI::Window* FrameWindowComponent::getCEGuiWindow()
		{
			return window;
		}
		
		void FrameWindowComponent::addChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			window->addChild(child->getCEGuiWindow());
		}

		void FrameWindowComponent::removeChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			window->removeChild(child->getCEGuiWindow()->getID());
		}

		void FrameWindowComponent::_update()
		{
			fps_counter.nextFrame();
		}
		
		void FrameWindowComponent::updateFps(size_t fps)
		{
			window->setText(std::to_string(fps));
		}

		Core::IComponentInterface* FrameWindowComponent::getInterface ( const Core::ComponentType& type )
		{
			using namespace ComponentInterfaces;
			if(type == CEGuiParentWidgetComponent::getType()) return static_cast<CEGuiParentWidgetComponent*>(this);
			return nullptr;
		}
		
	}
}