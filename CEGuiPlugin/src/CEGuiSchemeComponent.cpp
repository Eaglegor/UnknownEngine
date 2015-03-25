#include <CEGuiSchemeComponent.h>
#include <CEGUI/Scheme.h>
#include <CEGUI/SchemeManager.h>

namespace UnknownEngine
{
	namespace GUI
	{
		CEGuiSchemeComponent::CEGuiSchemeComponent ( const char* name, Core::IComponent* context, const CEGuiSchemeDesc &desc) : 
		BaseCEGuiComponent ( name, context ),
		desc(desc),
		scheme(nullptr)
		{
		}
		
		void CEGuiSchemeComponent::internalInit()
		{
			scheme = &CEGUI::SchemeManager::getSingleton().createFromFile(desc.filename);
		}

		void CEGuiSchemeComponent::internalShutdown()
		{
			// Resource destruction is controlled by CEGUI itself
		}
	}
}