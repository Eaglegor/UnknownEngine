#include <CEGuiConsoleComponent.h>
#include <CEGUI/CEGUI.h>
#include <boost/algorithm/string/trim.hpp>

namespace UnknownEngine
{
	namespace GUI
	{
		
		static const char* SUBMIT_BUTTON_NAME = "Submit";
		static const char* EDITBOX_NAME = "Editbox";
		static const char* HISTORY_BOX_NAME = "History";
		
		CEGuiConsoleComponent::CEGuiConsoleComponent ( const char* name, const CEGuiConsoleComponentDesc& desc, ICEGuiContext* context ) : 
		BaseCEGuiComponent ( name, context ),
		desc(desc),
		window(nullptr),
		parent_window(desc.parent_window),
		input_context_mapper(desc.input_context_mapper),
		logger(name, desc.log_level),
		is_active(false)
		{
		}
		
		CEGuiConsoleComponent::~CEGuiConsoleComponent()
		{
		}

		void CEGuiConsoleComponent::internalInit()
		{
			if(!parent_window)
			{
				LOG_ERROR(logger, "No parent window provided. Can't create console window");
				return;
			}
			window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("ConsoleWindowLayout.layout");
			
			if(!window)
			{
				LOG_ERROR(logger, "Failed to create CEGUI console window");
			}
			
			parent_window->addChild(this);
			
			window->getChild(SUBMIT_BUTTON_NAME)->subscribeEvent(
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(
					&CEGuiConsoleComponent::onTextSubmitted,
					this)
				);
			
			window->getChild(EDITBOX_NAME)->subscribeEvent(
				CEGUI::Editbox::EventTextAccepted,
				CEGUI::Event::Subscriber(
					&CEGuiConsoleComponent::onTextSubmitted,
					this)
				);
			
			output_stream.setListBox(static_cast<CEGUI::Listbox*>(window->getChild(HISTORY_BOX_NAME)));
			
			addCommandHandler("echo", &echo_handler);
			
			if(input_context_mapper)
			{
				window->setVisible(false);
				
				input_context_mapper->addSimpleAction(desc.game_context_name.c_str(), "System_OpenConsole", std::bind(&CEGuiConsoleComponent::activate, this));
				input_context_mapper->addSimpleAction(desc.console_context_name.c_str(), "System_CloseConsole", std::bind(&CEGuiConsoleComponent::deactivate, this));
			}
		}

		void CEGuiConsoleComponent::internalShutdown()
		{
			if(window)
			{
				if(input_context_mapper)
				{
					input_context_mapper->removeSimpleAction(desc.game_context_name.c_str(), "System_OpenConsole");
					input_context_mapper->removeSimpleAction(desc.console_context_name.c_str(), "System_CloseConsole");
				}
				
				removeCommandHandler("echo", &echo_handler);
				parent_window->removeChild(this);
				CEGUI::WindowManager::getSingleton().destroyWindow(window);
				window = nullptr;
			}
		}

		ComponentInterfaces::ConsoleOutputStream& CEGuiConsoleComponent::getOutputStream()
		{
			return output_stream;
		}

		void CEGuiConsoleComponent::addCommandHandler ( const char* command, ComponentInterfaces::ConsoleCommandHandler* handler )
		{
			auto iter = command_handlers.find(command);
			if(iter == command_handlers.end()) iter = command_handlers.emplace(command, CommandHandlersSet()).first;
			iter->second.emplace(handler);
		}
		
		void CEGuiConsoleComponent::removeCommandHandler ( const char* command, ComponentInterfaces::ConsoleCommandHandler* handler )
		{
			auto iter = command_handlers.find(command);
			if(iter==command_handlers.end()) return;
			iter->second.erase(handler);
		}
		
		void CEGuiConsoleComponent::_update()
		{
			if(window) window->setVisible(is_active);
		}
		
		void CEGuiConsoleComponent::addChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			window->addChild(child->getCEGuiWindow());
		}
		
		void CEGuiConsoleComponent::removeChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			window->removeChild(child->getCEGuiWindow()->getID());
		}

		CEGUI::Window* CEGuiConsoleComponent::getCEGuiWindow()
		{
			return window;
		}

		bool CEGuiConsoleComponent::onTextSubmitted ( const CEGUI::EventArgs& e )
		{
			CEGUI::String command = window->getChild(EDITBOX_NAME)->getText();
			processCommand(command.c_str());
			
			window->getChild(EDITBOX_NAME)->setText("");
			
			return true;
		}
		
		void CEGuiConsoleComponent::processCommand ( const char* command )
		{
			std::string s_command(command);
			boost::algorithm::trim(s_command);
			size_t first_space = s_command.find(" ");
			s_command = s_command.substr(0, first_space);
			
			boost::algorithm::to_lower(s_command);
			
			auto iter = command_handlers.find(s_command);
			if(iter == command_handlers.end())
			{
				LOG_ERROR(logger, "Unknown console command: " + s_command);
				output_stream << std::string("Unknown console command: " + s_command).c_str();
				return;
			}
			
			CommandHandlersSet &handlers = iter->second;
			for(ComponentInterfaces::ConsoleCommandHandler *handler : handlers)
			{
				handler->onConsoleCommand(command, output_stream);
			}
			
		}
	
		ComponentInterfaces::ConsoleOutputStream& CEGuiConsoleComponent::SimpleOutputStream::operator<< ( const char* text )
		{
			CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(text);
			output->addItem(item);
			return *this;
		}

		void CEGuiConsoleComponent::activate()
		{
			is_active = true;
			input_context_mapper->setCurrentContext(desc.console_context_name.c_str());
		}

		void CEGuiConsoleComponent::deactivate()
		{
			is_active = false;
			input_context_mapper->setCurrentContext(desc.game_context_name.c_str());
		}
	
	}
}