#include <AngelScriptSubsystem.h>
#include <Logging.h>
#include <AngelScriptMessageCallback.h>

#include <Registrators/Basic/StdStringRegistrator.h>
#include <Registrators/Core/ComponentSystem/ComponentDescRegistrator.h>
#include <Registrators/Core/Engine/EngineContextRegistrator.h>
#include <Registrators/Core/ComponentSystem/IComponentRegistrator.h>
#include <Registrators/Core/ComponentSystem/ComponentsManagerRegistrator.h>
#include <Registrators/Core/ComponentSystem/EntityRegistrator.h>
#include <Registrators/Core/Engine/PropertiesRegistrator.h>
#include <Registrators/Core/Engine/ILoggerRegistrator.h>
#include <Registrators/Core/ResourceManager/DataProviderDescRegistrator.h>
#include <Registrators/Core/ResourceManager/IDataProviderRegistrator.h>
#include <Registrators/Core/ResourceManager/ResourceManagerRegistrator.h>
#include <Registrators/Utils/NameGeneratorRegistrator.h>
#include <Registrators/Utils/StdOutPrintRegistrator.h>
#include <Registrators/Utils/LogSeverityRegistrator.h>

#include <scriptbuilder/scriptbuilder.h>

#include <iostream>

#include <iostream>

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

namespace UnknownEngine
{
	namespace Behavior
	{
		AngelScriptSubsystem::AngelScriptSubsystem (const std::string& name, const AngelScriptSubsystemDesc& desc, Core::EngineContext* engine_context ):
		engine_context(engine_context),
		desc(desc)
		{
			logger = CREATE_LOGGER(name, desc.log_level);
			angel_script_error_logger = logger;
		}

		AngelScriptSubsystem::~AngelScriptSubsystem()
		{
			angel_script_error_logger = nullptr;
			RELEASE_LOGGER(logger);
		}

		void AngelScriptSubsystem::init()
		{
			script_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
			script_engine->SetMessageCallback(asFUNCTION(angelScriptMessageCallback), 0, asCALL_CDECL);

			registerStandardTypes();
			
			script_engine->RegisterGlobalProperty("Core::EngineContext @engine_context", &engine_context);
		}
				
		void AngelScriptSubsystem::shutdown()
		{
			script_engine->Release();
		}
		
		void stubConstructor(asIObjectType* obj, void* memory)
		{
			std::cout << "Unimplemented constructor called" << std::endl;
		}
		
		void stubDestructor(void* memory)
		{
			std::cout << "Unimplemented destructor called" << std::endl;
		}
		
		
		void* stub_factory(void*)
		{
			return nullptr;
		};
		
		void stub_addref(void*)
		{
		}
		
		void stub_release(void*)
		{
		}
		
		void AngelScriptSubsystem::registerDefaultTemplatesPredefinition()
		{
			script_engine->SetDefaultNamespace("Core");
			
			script_engine->RegisterObjectType("ComponentInterfacePtr<class T>", 0, asOBJ_REF | asOBJ_TEMPLATE );
			script_engine->RegisterObjectBehaviour("ComponentInterfacePtr<T>", asBEHAVE_FACTORY, "ComponentInterfacePtr<T>@ f(int &in)", asFUNCTION(stub_factory), asCALL_CDECL);
			script_engine->RegisterObjectBehaviour("ComponentInterfacePtr<T>", asBEHAVE_ADDREF, "void f()", asFUNCTION(stub_addref), asCALL_CDECL_OBJFIRST);
			script_engine->RegisterObjectBehaviour("ComponentInterfacePtr<T>", asBEHAVE_RELEASE, "void f()", asFUNCTION(stub_release), asCALL_CDECL_OBJFIRST);
			
			script_engine->SetDefaultNamespace("");
		}

		
		void AngelScriptSubsystem::registerStandardTypes()
		{
			registerDefaultTemplatesPredefinition();

			registerObjectType(StdStringRegistrator());
			
			registerObjectType(LogSeverityRegistrator());
			registerObjectType(ILoggerRegistrator());
			
			registerObjectType(NameGeneratorRegistrator());
			registerObjectType(IDataProviderRegistrator());
			registerObjectType(PropertiesRegistrator());
			registerObjectType(ComponentDescRegistrator());
			registerObjectType(IComponentRegistrator());
			registerObjectType(EntityRegistrator());
			registerObjectType(ComponentsManagerRegistrator());
			registerObjectType(DataProviderDescRegistrator());
			registerObjectType(ResourceManagerRegistrator());
			
			registerObjectType(EngineContextRegistrator());
			
			registerObjectType(StdOutPrintRegistrator());
			
		}
		
		asIScriptEngine* UnknownEngine::Behavior::AngelScriptSubsystem::getScriptEngine()
		{
			return script_engine;
		}

		void AngelScriptSubsystem::registerObjectType ( const ITypeRegistrator& registrator )
		{
			if(!registrator.registerType(script_engine)) LOG_ERROR(logger, "Object type " + std::string(registrator.getRegisteredNameWithNamespace()) + " was not registered");
		}
	}
}
