#include <AngelScriptSubsystem.h>
#include <LogHelper.h>
#include <AngelScriptMessageCallback.h>

#include <Registrators/Basic/StdStringRegistrator.h>
#include <Registrators/Core/ComponentSystem/ComponentDescRegistrator.h>
#include <Registrators/Core/Engine/EngineContextRegistrator.h>
#include <Registrators/Core/ComponentSystem/IComponentRegistrator.h>
#include <Registrators/Core/ComponentSystem/ComponentsManagerRegistrator.h>
#include <Registrators/Core/ComponentSystem/EntityRegistrator.h>
#include <Registrators/Core/Engine/PropertiesRegistrator.h>
#include <Registrators/Core/ResourceManager/DataProviderDescRegistrator.h>
#include <Registrators/Core/ResourceManager/IDataProviderRegistrator.h>
#include <Registrators/Core/MessageSystem/ReceivedMessageDescRegistrator.h>
#include <Registrators/Core/MessageSystem/ReceivePolicyDescRegistrator.h>
#include <Registrators/Utils/NameGeneratorRegistrator.h>

#include <scriptbuilder/scriptbuilder.h>

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
			{// Utils
				NameGeneratorRegistrator().registerType(script_engine);
			}
			{// Core
				PropertiesRegistrator().registerType(script_engine);

				ReceivePolicyDescRegistrator().registerType(script_engine);
				ReceivedMessageDescRegistrator().registerType(script_engine);
				ComponentDescRegistrator().registerType(script_engine);
				IComponentRegistrator().registerType(script_engine);
				
				EntityRegistrator().registerType(script_engine);
				ComponentsManagerRegistrator().registerType(script_engine);
				EngineContextRegistrator().registerType(script_engine);
			}
			{// Loader
				DataProviderDescRegistrator().registerType(script_engine);
				IDataProviderRegistrator().registerType(script_engine);
			}
			{// Message types
				
			}
		}
	}
}