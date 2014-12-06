#pragma once

#include <Descriptors/AngelScriptSubsystemDesc.h>
#include <memory>
#include <unordered_map>

#include <ASIncludes.h>

namespace UnknownEngine
{
	
	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Behavior
	{
		class ITypeRegistrator;
		class AngelScriptSubsystem
		{
		public:
			AngelScriptSubsystem(const std::string& name, const AngelScriptSubsystemDesc& desc, Core::EngineContext* engine_context);
			~AngelScriptSubsystem();

			void init();
			void shutdown();

			asIScriptEngine* getScriptEngine();
			
		private:
			void registerDefaultTemplatesPredefinition();
			void registerStandardTypes();
			void registerObjectType(const ITypeRegistrator& registrator);
			void registerMessageType(const ITypeRegistrator& registrator);
			
			std::string name;
			Core::ILogger* logger;
			
			Core::EngineContext* engine_context;
			AngelScriptSubsystemDesc desc;

			asIScriptEngine *script_engine;
			
			std::unordered_map<std::string, asIScriptModule*> modules;
			
		};
	}
}