#include <ESGUIComponentsFactory.h>
#include <Properties/Properties.h>
#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/ComponentDesc.h>
#include <ESGUIHintComponentDesc.h>
#include <ESGUIHintComponent.h>
#include <ESGUICrosshairComponentDesc.h>
#include <ESGUICrosshairComponent.h>
#include <ESGUIRestartButtonComponentDesc.h>
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

			creatable_object.type = ESGUICrosshairComponent::getTypeName();
			creatable_object.creator = std::bind(&ESGUIComponentsFactory::createESCrosshairComponent, this, std::placeholders::_1);
			creatable_object.deleter = std::bind(&ESGUIComponentsFactory::destroyESCrosshairComponent, this, std::placeholders::_1);
			registerCreator(creatable_object);
		}

		Core::IComponent* ESGUIComponentsFactory::createESHintComponent(const Core::ComponentDesc &desc)
		{
			const Core::Properties &props = boost::get<Core::Properties>(desc.descriptor);
			ESGUIHintComponentDesc descriptor;
			descriptor = props;
			return new ESGUIHintComponent(desc.name.c_str(), descriptor);
		}

		void ESGUIComponentsFactory::destroyESHintComponent ( Core::IComponent* component )
		{
			(static_cast<ESGUIHintComponent*>(component))->startDestruction(DefaultDestructionFunctor());
		}
		
		Core::IComponent* ESGUIComponentsFactory::createESRestartButtonComponent(const Core::ComponentDesc &desc)
		{
			const Core::Properties &props = boost::get<Core::Properties>(desc.descriptor);
			ESGUIRestartButtonComponentDesc descriptor;
			descriptor = props;
			if(!descriptor.isValid()) return nullptr;
			return nullptr;
		}

		void ESGUIComponentsFactory::destroyESRestartButtonComponent ( Core::IComponent* component )
		{

		}

		Core::IComponent* ESGUIComponentsFactory::createESCrosshairComponent(const Core::ComponentDesc &desc)
		{
			const Core::Properties &props = boost::get<Core::Properties>(desc.descriptor);
			ESGUICrosshairComponentDesc descriptor;
			descriptor = props;
			if(!descriptor.isValid()) return nullptr;
			return new ESGUICrosshairComponent(desc.name.c_str(), descriptor);
		}

		void ESGUIComponentsFactory::destroyESCrosshairComponent ( Core::IComponent* component )
		{
			(static_cast<ESGUICrosshairComponent*>(component))->startDestruction(DefaultDestructionFunctor());
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
