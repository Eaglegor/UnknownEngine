#include <AngelScriptSubsystem.h>
#include <LogHelper.h>
#include <AngelScriptMessageCallback.h>
#include <Registrators/Basic/StdStringRegistrator.h>
#include <Registrators/Core/ComponentDescRegistrator.h>
#include <Registrators/Core/EngineContextRegistrator.h>
#include <Registrators/Core/IComponentRegistrator.h>
#include <scriptbuilder.h>
#include <scriptstdstring.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Behavior
	{
		AngelScriptSubsystem::AngelScriptSubsystem (const std::string& name, const AngelScriptSubsystemDesc& desc, Core::EngineContext* engine_context ):
		engine_context(engine_context),
		desc(desc)
		{
			if(desc.log_level > Utils::LogSeverity::NONE)
			{
				log_helper.reset(new Utils::LogHelper(name, desc.log_level, engine_context));
				
				angel_script_error_logger = log_helper.get();
			}
		}

		AngelScriptSubsystem::~AngelScriptSubsystem()
		{
			angel_script_error_logger = nullptr;
		}

		void AngelScriptSubsystem::init()
		{
			script_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
			script_engine->SetMessageCallback(asFUNCTION(angelScriptMessageCallback), 0, asCALL_CDECL);

			registerStandardTypes();
			
			script_engine->RegisterGlobalProperty("EngineContext @engine_context", engine_context);
		}
				
		void AngelScriptSubsystem::shutdown()
		{
			script_engine->Release();
		}
		
		void AngelScriptSubsystem::registerStandardTypes()
		{
			{// Basic types
				StdStringRegistrator().registerType(script_engine);
			}
			{// Core engine types
				IComponentRegistrator("IComponent").registerType(script_engine);
				ComponentDescRegistrator("ComponentDesc").registerType(script_engine);
				EngineContextRegistrator("EngineContext").registerType(script_engine);
			}
		}
	}
}