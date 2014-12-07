#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <Descriptors/AngelScriptComponentDesc.h>
#include <AngelScriptSubsystem.h>
#include <memory>
#include <unordered_map>

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
			AngelScriptComponent ( const std::string& name, const AngelScriptComponentDesc& desc, Core::EngineContext* engine_context, AngelScriptSubsystem* angel_script_subsystem );
			virtual ~AngelScriptComponent();
			
			virtual UnknownEngine::Core::ComponentType getType() const;
			
			virtual void init ( const Core::IEntity* parent_entity );
			virtual void shutdown();
			
			static const Core::ComponentType TYPE;
		private:
			Core::ILogger* logger;
			AngelScriptComponentDesc desc;
			Core::EngineContext* engine_context;
			asIScriptModule* module;
			asIScriptContext* context;
		
			AngelScriptSubsystem* angel_script_subsystem;
		};
	}
}