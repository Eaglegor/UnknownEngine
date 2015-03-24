#pragma once
#include <ICEGuiContext.h>
#include <CEGuiConsoleComponentDesc.h>
#include <BaseCEGuiComponent.h>
#include <ComponentInterfaces/GUI/Common/Console/ConsoleWindow.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiWidgetComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Input/Common/IContextualActionsMapper.h>
#include <unordered_map>
#include <unordered_set>
#include <LogHelper.h>

namespace CEGUI
{
	class Window;
	class EventArgs;
	class Listbox;
}

namespace UnknownEngine
{
	namespace GUI
	{
		class CEGuiConsoleComponent : 
		public BaseCEGuiComponent,
		public ComponentInterfaces::ConsoleWindow,
		public ComponentInterfaces::CEGuiWidgetComponent
		{
		public:
			CEGuiConsoleComponent(const char* name, const CEGuiConsoleComponentDesc &desc, Core::IComponent *context);
			~CEGuiConsoleComponent();
			
			constexpr static const char* getTypeName() {return "CEGUI.ConsoleWindow";}
			virtual Core::ComponentType getType() const {return getTypeName();}

			virtual void _update();
			
			virtual void internalInit();
			virtual void internalShutdown();
			
			virtual void addCommandHandler ( const char* command, ComponentInterfaces::ConsoleCommandHandler* handler ) override;
			virtual void removeCommandHandler ( const char* command, ComponentInterfaces::ConsoleCommandHandler* handler ) override;

			virtual ComponentInterfaces::ConsoleOutputStream& getOutputStream() override;
			
			virtual void addChild ( CEGuiWidgetComponent* child );
			virtual void removeChild ( CEGuiWidgetComponent* child );
			
			virtual CEGUI::Window* getCEGuiWindow();

			virtual void activate();
			virtual void deactivate();
			
		private:
			class SimpleOutputStream : public ComponentInterfaces::ConsoleOutputStream
			{
			public:
				SimpleOutputStream()
				{}
				
				void setListBox(CEGUI::Listbox* box){output = box;}
				virtual ConsoleOutputStream& operator<< ( const char* text );
				
			private:
				CEGUI::Listbox* output;
			};
			
			class SimpleEchoHandler : public ComponentInterfaces::ConsoleCommandHandler
			{
			public:
				virtual void onConsoleCommand ( const char* command, ComponentInterfaces::ConsoleOutputStream& ostream )
				{
					ostream << command;
				}
			};
			
			bool onTextSubmitted(const CEGUI::EventArgs &e);
			
			void processCommand(const char* command);
			
			CEGuiConsoleComponentDesc desc;
			CEGUI::Window* window;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::CEGuiWidgetComponent> parent_window;
			Core::ComponentInterfacePtr<ComponentInterfaces::IContextualActionsMapper> input_context_mapper;
			Core::LogHelper logger;
			
			typedef std::unordered_set<ComponentInterfaces::ConsoleCommandHandler*> CommandHandlersSet;
			typedef std::unordered_map<std::string, CommandHandlersSet> CommandHandlersMap;
			
			CommandHandlersMap command_handlers;
			
			SimpleOutputStream output_stream;
			SimpleEchoHandler echo_handler;
			
			bool is_active;
		};
	}
}