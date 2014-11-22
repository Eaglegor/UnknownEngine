#include <AngelScriptSubsystem.h>
#include <LogHelper.h>
#include <AngelScriptMessageCallback.h>
#include <scriptbuilder.h>
#include <scriptstdstring.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Behavior
	{
		AngelScriptSubsystem::AngelScriptSubsystem (const std::string& name, const AngelScriptSubsystemDesc& desc, Core::EngineContext* engine_context ):
		desc(desc),
		engine_context(engine_context)
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
		}
				
		void AngelScriptSubsystem::shutdown()
		{
			script_engine->Release();
		}
		
		void AngelScriptSubsystem::registerStandardTypes()
		{
			RegisterStdString(script_engine);
		}
	}
}