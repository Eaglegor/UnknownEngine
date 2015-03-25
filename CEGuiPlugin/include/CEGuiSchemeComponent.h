#pragma once

#include <BaseCEGuiComponent.h>
#include <CEGuiSchemeDesc.h>

namespace CEGUI
{
	class Scheme;
}

namespace UnknownEngine
{
	namespace GUI
	{
		class CEGuiSchemeComponent : public BaseCEGuiComponent
		{
		public:
			CEGuiSchemeComponent(const char* name, Core::IComponent* context, const CEGuiSchemeDesc &desc);
			constexpr static const char* getTypeName(){return "CEGUI.Scheme";}
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual void internalInit();
			virtual void internalShutdown();
			virtual void _update(){};
			
		private:
			CEGuiSchemeDesc desc;
			CEGUI::Scheme* scheme;
		};
	}
}