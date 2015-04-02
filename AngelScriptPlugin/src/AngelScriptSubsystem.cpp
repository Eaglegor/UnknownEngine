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

#include <string>

#include <ASBind/RefClass.h>
#include <ASBind/ValueClass.h>
#include <ASBind/Enum.h>

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
			
			//script_engine->RegisterGlobalProperty("Core::EngineContext @engine_context", &engine_context);
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

		class DummyClass
		{
		public:
			
			DummyClass():
			name("UnspecifiedName")
			{
				std::cout << "Ctor " << name << std::endl;
			}
			
			DummyClass(const std::string& name):
			name(name)
			{
				std::cout << "Ctor " << name << std::endl;
			}
			
			DummyClass(const DummyClass& rhs):
			name(rhs.name + "_cp")
			{
				std::cout << "CopyCtor " << name << std::endl;
			}
			
			DummyClass& operator=(const DummyClass& rhs)
			{
				name = name + "=" + rhs.name;
				std::cout << "Operator=" << name << std::endl;
				return *this;
			}
			
			virtual ~DummyClass()
			{
				std::cout << "Dtor " << name << std::endl;
			}
			
			void method1()
			{
				std::cout << "method1" << std::endl;
			}
			
			void method2(const DummyClass &cls)
			{
				std::cout << "method2" << std::endl;
			}
			
			void method3(DummyClass *cls)
			{
				std::cout << "method3" << std::endl;
			}
			
			void method4(DummyClass cls)
			{
				std::cout << "method4" << std::endl;
			}
			
			int method5(DummyClass cls, int a)
			{
				std::cout << "method5" << std::endl;
				return 1;
			}
			
			DummyClass method6(DummyClass cls, int a)
			{
				std::cout << "method6" << std::endl;
				DummyClass cls2("temporary");
				return cls2;
			}
			
			static void method7()
			{
				std::cout << "Method7" << std::endl;
			}
			
			std::string name;
			
		};
		
		void AngelScriptSubsystem::registerStandardTypes()
		{
			registerDefaultTemplatesPredefinition();

			registerObjectType(StdStringRegistrator());
			
			bindTypeInfo<void>("void", ASBind::ClassType::PRIMITIVE_TYPE);
			bindTypeInfo<int>("int", ASBind::ClassType::PRIMITIVE_TYPE);
			bindTypeInfo<std::string>("std::string", ASBind::ClassType::VALUE_TYPE);
			
			ASBind::Enum("SampleEnum", this)
			.value("HELLO", 1)
			.value("BYE", 2);
			
			ASBind::RefClass<DummyClass>("DummyClass", this)
			.constructor<>()
			.constructor<const std::string&>()
			.constructor<const DummyClass&>()
			.ref_counter()
			//.destructor()
			.method(&DummyClass::method1, "method1")
			.method(&DummyClass::method2, "method2")
			.method(&DummyClass::method3, "method3")
			.method(&DummyClass::method4, "method4")
			.method(&DummyClass::method5, "method5")
			.method(&DummyClass::method6, "method6")
			.static_method(&DummyClass::method7, "method7")
			.operatorAssign();
			
			//.method(&DummyClass::method4, "method4");
			
			/*registerObjectType(LogSeverityRegistrator());
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
			
			registerObjectType(StdOutPrintRegistrator());*/
			
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
