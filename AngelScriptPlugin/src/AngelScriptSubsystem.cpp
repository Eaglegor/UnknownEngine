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
#include <Registrators/Core/Messages/StopEngineActionMessageRegistrator.h>
#include <Registrators/Utils/NameGeneratorRegistrator.h>
#include <Registrators/Utils/StdOutPrintRegistrator.h>

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
			
			script_engine->RegisterGlobalProperty("Core::EngineContext @engine_context", engine_context);
		}
				
		void AngelScriptSubsystem::shutdown()
		{
			script_engine->Release();
		}
		
		void AngelScriptSubsystem::registerStandardTypes()
		{
			// Predefining templates
			//script_engine->SetDefaultNamespace("Core");
				//script_engine->RegisterObjectType("MessageSender<class T>", sizeof(Core::MessageSender<Core::StopEngineActionMessage>), asOBJ_VALUE | asOBJ_TEMPLATE );
				//script_engine->RegisterObjectType("MessageListener<class T>", sizeof(AngelScriptMessageListener<Core::StopEngineActionMessage>), asOBJ_VALUE | asOBJ_TEMPLATE );
			//script_engine->SetDefaultNamespace("");
			
			registerObjectType(StdStringRegistrator());
			registerObjectType(NameGeneratorRegistrator());
			registerObjectType(IDataProviderRegistrator());
			registerObjectType(PropertiesRegistrator());
			registerObjectType(ReceivePolicyDescRegistrator());
			registerObjectType(ReceivedMessageDescRegistrator());
			registerObjectType(ComponentDescRegistrator());
			registerObjectType(IComponentRegistrator());
			registerObjectType(EntityRegistrator());
			registerObjectType(ComponentsManagerRegistrator());
			registerObjectType(EngineContextRegistrator());
			registerObjectType(DataProviderDescRegistrator());
			
			registerObjectType(StdOutPrintRegistrator());
			
			//registerMessageType(StopEngineActionMessageRegistrator);
		}
		
		asIScriptEngine* UnknownEngine::Behavior::AngelScriptSubsystem::getScriptEngine()
		{
			return script_engine;
		}

		void AngelScriptSubsystem::registerObjectType ( const ITypeRegistrator& registrator )
		{
			if(!registrator.registerType(script_engine)) LOG_ERROR(log_helper, "Object type " + std::string(registrator.getRegisteredName()) + " was not registered");
		}

		void AngelScriptSubsystem::registerMessageType ( const IMessageTypeRegistrator& registrator )
		{
			if(!registrator.registerType(script_engine)) {
				LOG_ERROR(log_helper, "Message type " + std::string(registrator.getRegisteredName()) + " was not registered");
			}
			else
			{
				if(!registrator.registerSender(script_engine))
				{
					LOG_ERROR(log_helper, "Message sender type for message type " + std::string(registrator.getRegisteredName()) + " was not registered");
				}
				if(!registrator.registerListener(script_engine))
				{
					LOG_ERROR(log_helper, "Message listener type for message type " + std::string(registrator.getRegisteredName()) + " was not registered");
				}
			}
		}
		
	}
}