#pragma once
#include <Registrators/ITypeRegistrator.h>
#include <EngineContext.h>
#include <string>
#include <iostream>

namespace UnknownEngine
{
	namespace Behavior
	{
		class StdOutPrintRegistrator : public ITypeRegistrator
		{
		public:
			virtual const char* getRegisteredName() const override
			{
				return "StdOutPrintUtils";
			}
			
			virtual const char* getRegisteredNameWithNamespace() const
			{
				return "std::StdOutPrintUtils";
			}
			
			static void print_to_stdout(const std::string &text)
			{
				std::cout << text << std::endl;
			}
			
			static Core::EngineContext* EngineContextChecker(Core::EngineContext* engine_context)
			{
				return engine_context;
			}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const
			{
				int result = script_engine->RegisterGlobalFunction("void print(const std::string &in)", asFUNCTION(StdOutPrintRegistrator::print_to_stdout), asCALL_CDECL);
				if(result < 0 ) return false;
				result = script_engine->RegisterGlobalFunction("void check(Core::EngineContext@)", asFUNCTION(StdOutPrintRegistrator::EngineContextChecker), asCALL_CDECL);
				return true;
			}
		};
	}
}