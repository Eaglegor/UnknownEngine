#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <Descriptors/AngelScriptComponentDesc.h>
#include <AngelScriptSubsystem.h>
#include <memory>
#include <unordered_map>
#include <LogHelper.h>

namespace UnknownEngine
{
	
	namespace Core
	{
		class ILogger;
	}
	
	namespace Behavior
	{

		template<class MessageType >
		class AngelScriptMessageListener;
		class AngelScriptComponent : public Core::BaseComponent
		{
		public:
			AngelScriptComponent ( const char* name, const AngelScriptComponentDesc& desc, AngelScriptSubsystem* angel_script_subsystem );
			virtual ~AngelScriptComponent();
			
			virtual UnknownEngine::Core::ComponentType getType() const;
			
			virtual bool init ();
			virtual void shutdown();
			
			static const Core::ComponentType TYPE;
		private:
			Core::LogHelper logger;
			AngelScriptComponentDesc desc;
			asIScriptModule* module;
			asIScriptContext* context;
		
			AngelScriptSubsystem* angel_script_subsystem;
		};
	}
}