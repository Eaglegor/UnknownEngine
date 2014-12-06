#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ILoggerRegistrator : public ClassReferenceTypeRegistrator<Core::ILogger>
		{
		public:
			ILoggerRegistrator ():
			ClassReferenceTypeRegistrator<Core::ILogger>("ILogger", CORE_AS_NAMESPACE_NAME)
			{}
			
			static void log_info(Core::ILogger* logger, const std::string& message)
			{
				LOG_INFO(logger, message);
			}
			
			static void log_debug(Core::ILogger* logger, const std::string& message)
			{
				LOG_DEBUG(logger, message);
			}
			
			static void log_warning(Core::ILogger* logger, const std::string& message)
			{
				LOG_WARNING(logger, message);
			}
			
			static void log_error(Core::ILogger* logger, const std::string& message)
			{
				LOG_ERROR(logger, message);
			}
			
			static Core::ILogger* create_logger(const std::string &name, Core::LogSeverity log_level)
			{
				return CREATE_LOGGER(name, log_level);
			}
			
			static void release_logger(Core::ILogger* logger)
			{
				return RELEASE_LOGGER(logger);
			}
			
		protected:
			virtual bool registerMethods ( asIScriptEngine* script_engine ) const
			{
				int result;
				
				script_engine->SetDefaultNamespace("");
				
				result = script_engine->RegisterGlobalFunction("void LOG_INFO(Core::ILogger@, const std::string &in)", asFUNCTION(ILoggerRegistrator::log_info), asCALL_CDECL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterGlobalFunction("void LOG_ERROR(Core::ILogger@, const std::string &in)", asFUNCTION(ILoggerRegistrator::log_error), asCALL_CDECL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterGlobalFunction("void LOG_WARNING(Core::ILogger@, const std::string &in)", asFUNCTION(ILoggerRegistrator::log_warning), asCALL_CDECL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterGlobalFunction("void LOG_DEBUG(Core::ILogger@, const std::string &in)", asFUNCTION(ILoggerRegistrator::log_debug), asCALL_CDECL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterGlobalFunction("Core::ILogger@ CREATE_LOGGER(const std::string &in, Core::LogSeverity)", asFUNCTION(ILoggerRegistrator::create_logger), asCALL_CDECL);
				if(result < 0 ) return false;
				
				result = script_engine->RegisterGlobalFunction("void RELEASE_LOGGER(Core::ILogger@)", asFUNCTION(ILoggerRegistrator::release_logger), asCALL_CDECL);
				if(result < 0 ) return false;
				
				script_engine->SetDefaultNamespace(CORE_AS_NAMESPACE_NAME.c_str());
				
				return true;
			}
			
		};
	}
}