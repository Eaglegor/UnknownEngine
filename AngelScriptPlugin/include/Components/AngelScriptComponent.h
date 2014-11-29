#pragma once

#include <Objects/BaseComponent.h>
#include <Descriptors/AngelScriptComponentDesc.h>
#include <AngelScriptSubsystem.h>
#include <memory>
#include <unordered_map>

namespace UnknownEngine
{
	
	namespace Utils
	{
		class LogHelper;
	}
	
	namespace Behavior
	{

		template<class MessageType >
		class AngelScriptMessageListener;
		class AngelScriptComponent : public Core::BaseComponent
		{
		public:
			AngelScriptComponent ( const std::string& name, const AngelScriptComponentDesc& desc, Core::EngineContext* engine_context, AngelScriptSubsystem* angel_script_subsystem );
			
			virtual UnknownEngine::Core::ComponentType getType() const;
			
			virtual void init ( const Core::Entity* parent_entity );
			virtual void shutdown();
			
			static const Core::ComponentType TYPE;
		private:
			std::unique_ptr<Utils::LogHelper> log_helper;
			AngelScriptComponentDesc desc;
			Core::EngineContext* engine_context;
		
			AngelScriptSubsystem* angel_script_subsystem;
		};
	}
}