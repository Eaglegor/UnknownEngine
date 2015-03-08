#include <stdafx.h>

#include <CEGuiContextFactory.h>
#include <OgreSynchronizedCEGuiContext.h>
#include <OgreSeparateThreadCEGuiContext.h>
#include <FrameWindowComponent.h>
#include <OgreCEGuiContextDesc.h>
#include <ComponentSystem/ComponentDesc.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace GUI
	{
		CEGuiContextFactory::CEGuiContextFactory ()
		{
			CreatableObjectDesc creatable_object;
			
			creatable_object.type = OgreSynchronizedCEGuiContext::getTypeName();
			creatable_object.creator = std::bind(&CEGuiContextFactory::createSynchronizedOgreContext, this, std::placeholders::_1);
			registerCreator(creatable_object);
			
			creatable_object.type = OgreSeparateThreadCEGuiContext::getTypeName();
			creatable_object.creator = std::bind(&CEGuiContextFactory::createSeparateThreadOgreContext, this, std::placeholders::_1);
			registerCreator(creatable_object);
			
			creatable_object.type = FrameWindowComponent::getTypeName();
			creatable_object.creator = std::bind(&CEGuiContextFactory::createFrameWindow, this, std::placeholders::_1);
			registerCreator(creatable_object);
		}
		
		Core::IComponent* CEGuiContextFactory::createSynchronizedOgreContext ( const Core::ComponentDesc &desc )
		{
			const Core::Properties &props = boost::get<Core::Properties>(desc.descriptor);
			Core::IComponent* render_window = Core::ComponentsManager::getSingleton()->findComponent((props.get<std::string>("render_window")).c_str());
			Core::LogSeverity log_severity = boost::lexical_cast<Core::LogSeverity>(props.get<std::string>("log_level", "none"));
			OgreCEGuiContextDesc subsystem_desc;
			subsystem_desc.render_window = render_window;
			subsystem_desc.log_level = log_severity;
			subsystem_desc.mouse_handler = Core::ComponentsManager::getSingleton()->findComponent((props.get<std::string>("mouse_handler")).c_str());
			subsystem_desc.keyboard_handler = Core::ComponentsManager::getSingleton()->findComponent((props.get<std::string>("keyboard_handler")).c_str());
			return new OgreSynchronizedCEGuiContext(desc.name.c_str(), subsystem_desc);
		}
		
		Core::IComponent* CEGuiContextFactory::createSeparateThreadOgreContext ( const Core::ComponentDesc &desc )
		{
			const Core::Properties &props = boost::get<Core::Properties>(desc.descriptor);
			Core::IComponent* render_window = Core::ComponentsManager::getSingleton()->findComponent((props.get<std::string>("render_window")).c_str());
			Core::LogSeverity log_severity = boost::lexical_cast<Core::LogSeverity>(props.get<std::string>("log_level", "none"));
			OgreCEGuiContextDesc subsystem_desc;
			subsystem_desc.render_window = render_window;
			subsystem_desc.log_level = log_severity;
			subsystem_desc.mouse_handler = Core::ComponentsManager::getSingleton()->findComponent((props.get<std::string>("mouse_handler")).c_str());
			subsystem_desc.keyboard_handler = Core::ComponentsManager::getSingleton()->findComponent((props.get<std::string>("keyboard_handler")).c_str());
			return new OgreSeparateThreadCEGuiContext(desc.name.c_str(), subsystem_desc);
		}
		
		Core::IComponent* CEGuiContextFactory::createFrameWindow ( const Core::ComponentDesc& desc )
		{
			const Core::Properties &props = boost::get<Core::Properties>(desc.descriptor);
			Core::IComponent* render_window = Core::ComponentsManager::getSingleton()->findComponent((props.get<std::string>("parent_window")).c_str());
			Core::LogSeverity log_severity = boost::lexical_cast<Core::LogSeverity>(props.get<std::string>("log_level", "none"));
			std::string title = props.get<std::string>("title");
			std::string type = props.get<std::string>("type");
			FrameWindowDesc subsystem_desc;
			subsystem_desc.parent_window = render_window;
			subsystem_desc.log_level = log_severity;
			subsystem_desc.window_caption = title;
			subsystem_desc.window_type = type;
			return new FrameWindowComponent(desc.name.c_str(), subsystem_desc);
		}
	}
}