#pragma once

#include <Registrators/ITypeRegistrator.h>
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class LogSeverityRegistrator : public ITypeRegistrator
		{
		public:
			virtual const char* getRegisteredName() const
			{
				return "LogSeverity";
			}
			
			virtual const char* getRegisteredNameWithNamespace() const
			{
				return "Core::LogSeverity";
			}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const
			{
				
				script_engine->SetDefaultNamespace("Core");
				int result;					
				result = script_engine->RegisterEnum("LogSeverity");
				if(result < 0) return false;
				
				result = script_engine->RegisterEnumValue("LogSeverity", "NONE", static_cast<int>(Core::LogSeverity::NONE));
				if(result < 0) return false;
				
				result = script_engine->RegisterEnumValue("LogSeverity", "INFO", static_cast<int>(Core::LogSeverity::INFO));
				if(result < 0) return false;
				
				result = script_engine->RegisterEnumValue("LogSeverity", "ERROR", static_cast<int>(Core::LogSeverity::ERROR_));
				if(result < 0) return false;
				
				result = script_engine->RegisterEnumValue("LogSeverity", "WARNING", static_cast<int>(Core::LogSeverity::WARNING));
				if(result < 0) return false;
				
				result = script_engine->RegisterEnumValue("LogSeverity", "DEBUG", static_cast<int>(Core::LogSeverity::DEBUG));
				if(result < 0) return false;
				
				script_engine->SetDefaultNamespace("");
				
				return true;
			}
			
		};
	}
}