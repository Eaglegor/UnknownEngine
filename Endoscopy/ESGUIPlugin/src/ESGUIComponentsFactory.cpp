#include <ESGUIComponentsFactory.h>
#include <Properties/Properties.h>
#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/ComponentDesc.h>
#include <ESGUIHintComponentDesc.h>
#include <ESGUIHintComponent.h>
#include <LogSeverity.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		ESGUIComponentsFactory::ESGUIComponentsFactory()
		{
			CreatableObjectDesc creatable_object;
			
			creatable_object.type = ESGUIHintComponent::getTypeName();
			creatable_object.creator = std::bind(&ESGUIComponentsFactory::createESHintComponent, this, std::placeholders::_1);
			creatable_object.deleter = std::bind(&ESGUIComponentsFactory::destroyESHintComponent, this, std::placeholders::_1);
			registerCreator(creatable_object);
		}

		Core::IComponent* ESGUIComponentsFactory::createESHintComponent(const Core::ComponentDesc &desc)
		{
			const Core::Properties &props = boost::get<Core::Properties>(desc.descriptor);
			Core::IComponent* parent_window = Core::ComponentsManager::getSingleton()->findComponent((props.get<std::string>("parent_window")).c_str());
			Core::IComponent* cegui_context = Core::ComponentsManager::getSingleton()->findComponent((props.get<std::string>("cegui_context")).c_str());
			Core::LogSeverity log_severity = boost::lexical_cast<Core::LogSeverity>(props.get<std::string>("log_level", "none"));
			ESGUIHintComponentDesc descriptor;
			descriptor.parent_window = parent_window;
			descriptor.cegui_context = cegui_context;
			descriptor.default_text = props.get<std::string>("default_text");
			descriptor.layout_filename = props.get<std::string>("layout_filename");
			descriptor.log_level = log_severity;
			return new ESGUIHintComponent(desc.name.c_str(), descriptor);
		}

		void ESGUIComponentsFactory::destroyESHintComponent ( Core::IComponent* component )
		{
			(static_cast<ESGUIHintComponent*>(component))->startDestruction(DefaultDestructionFunctor());
		}
		
		Core::IComponent* ESGUIComponentsFactory::createESRestartButtonComponent(const Core::ComponentDesc &desc)
		{
			return nullptr;
		}

		void ESGUIComponentsFactory::destroyESRestartButtonComponent ( Core::IComponent* component )
		{

		}

		
		Core::IComponent* ESGUIComponentsFactory::createESCrosshairComponent(const Core::ComponentDesc &desc)
		{
			return nullptr;
		}

		void ESGUIComponentsFactory::destroyESCrosshairComponent ( Core::IComponent* component )
		{

		}
		
		Core::IComponent* ESGUIComponentsFactory::createESInstrumentSelectorComponent(const Core::ComponentDesc &desc)
		{
			return nullptr;
		}
		
		void ESGUIComponentsFactory::destroyESInstrumentSelectorComponent ( Core::IComponent* component )
		{

		}

	}
}