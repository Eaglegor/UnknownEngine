#pragma once

#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
	}

	namespace Behavior
	{

		class AngelScriptSubsystem;
		class AngelScriptComponentFactory : public Core::BaseComponentFactory
		{
		public:
			AngelScriptComponentFactory(AngelScriptSubsystem* angel_script_subsystem);
			virtual const char* getName() const;
			
		private:
			Core::IComponent* createAngelScriptComponent(const Core::ComponentDesc &desc);
			
			AngelScriptSubsystem* angel_script_subsystem;
		};
	}
}