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

static std::unordered_map<std::type_index, std::string> bindings;

template<typename T>
struct FormattedTypeName
{
	std::string operator()()
	{
		auto iter = bindings.find(std::type_index(typeid(T)));
		if(iter != bindings.end())
		{
			return iter->second;
		}
		return "???";
	}
};

template<typename T>
struct DecoratedTypeName
{
	std::string operator()()
	{
		return FormattedTypeName<T>()();
	}
};

template<typename T>
struct DecoratedTypeName<const T&>
{
	std::string operator()()
	{
		return "const " + FormattedTypeName<T>()() + "&";
	}
};

template<typename T>
struct DecoratedTypeName<T&>
{
	std::string operator()()
	{
		return FormattedTypeName<T>()() + "&";
	}
};

template<typename T>
struct DecoratedTypeName<const T*>
{
	std::string operator()()
	{
		return "const " + FormattedTypeName<T>()() + "*";
	}
};

template<typename T>
struct DecoratedTypeName<T*>
{
	std::string operator()()
	{
		return FormattedTypeName<T>()() + "*";
	}
};

template<typename Arg, typename... Args>
struct FormattedArgumentsString
{
	std::string operator()()
	{
		return DecoratedTypeName<Arg>()() + ", " + FormattedArgumentsString<Args...>()();
	}
};

template<typename Arg>
struct FormattedArgumentsString<Arg>
{
	std::string operator()()
	{
		return DecoratedTypeName<Arg>()();
	}
};


template<typename RetVal, typename... Args>
std::string format_signature(RetVal (*f)(Args...), const std::string &name)
{
	return DecoratedTypeName<RetVal>()() + " " + name + "(" + FormattedArgumentsString<Args...>()() + ")";
}

template<typename RetVal>
std::string format_signature(RetVal (*f)(), const std::string &name)
{
	return DecoratedTypeName<RetVal>()() + " " + name + "()";
}

template<typename RetVal, typename T, typename... Args>
std::string format_member_signature(RetVal (T::*f)(Args...), const std::string &name)
{
	return DecoratedTypeName<RetVal>()() + " " + FormattedTypeName<T>()() + "::" + name + "(" + FormattedArgumentsString<Args...>()() + ")";
}

template<typename RetVal, typename T>
std::string format_member_signature(RetVal (T::*f)(), const std::string &name)
{
	return DecoratedTypeName<RetVal>()() + " " + FormattedTypeName<T>()() + "::" + name + "()";
}

template<typename T>
void bind_type_name(const std::string &name)
{
	bindings.emplace(std::type_index(typeid(T)), name);
};

template<typename T>
struct ASClass
{
	ASClass(const std::string &name, asIScriptEngine* script_engine):
	name(name),
	engine(script_engine)
	{
		bind_type_name<T>(name);
		engine->RegisterObjectType(name.c_str(), 0, asOBJ_REF);
	}
	
	template<typename Retval, typename... Args>
	ASClass& method(Retval (T::*f)(Args...), const std::string &name)
	{
		engine->RegisterObjectMethod(name, format_signature<Retval, Args...>(), asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(Retval (T::*)(Args...))(f)), asCALL_THISCALL);
		return *this;
	}
	
	template<typename Retval, typename... Args>
	ASClass& static_method(Retval (T::*f)(Args...), const std::string &name)
	{
		engine->RegisterGlobalFunction(format_signature(f), asFUNCTION(f), asCALL_CDECL);
	}
	
	template<typename... Args>
	ASClass& constructor()
	{
		engine->RegisterObjectBehaviour(name, asBEHAVE_FACTORY, name + "@ f(" + FormattedArgumentsString<Args...>()() + ")", asFUNCTION(ASClass<T>::defaultFactoryFunc), asCALL_CDECL);
	}

	ASClass& defaultRefcounter()
	{
		engine->RegisterObjectBehaviour(name, asBEHAVE_ADDREF, "void f()", asFUNCTION(ASClass<T>::addRef), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectBehaviour(name, asBEHAVE_RELEASE, "void f()", asFUNCTION(ASClass<T>::release), asCALL_CDECL_OBJFIRST);
	}
	
	ASClass& customRefcounter( void (T::*add_ref_behavior)(), void (T::*release_behavior)() )
	{
		engine->RegisterObjectBehaviour(name, asBEHAVE_ADDREF, "void f()", asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(void (T::*)())(add_ref_behavior)), asCALL_THISCALL);
		engine->RegisterObjectBehaviour(name, asBEHAVE_RELEASE, "void f()", asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(void (T::*)())(release_behavior)), asCALL_CDECL_OBJFIRST);
	}
	
	ASClass& static_customRefcounter(void (*add_ref_behavior) (T*), void (*release_behavior)(T*))
	{
		engine->RegisterObjectBehaviour(name, asBEHAVE_ADDREF, "void f()", asFUNCTION(add_ref_behavior), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectBehaviour(name, asBEHAVE_RELEASE, "void f()", asFUNCTION(release_behavior), asCALL_CDECL_OBJFIRST);
	}

private:
	template<typename... Args>
	static T* defaultFactoryFunc(Args&& ...args)
	{
		return new T(std::forward<Args>(args)...);
	}
	
	static void addRef(T* obj)
	{
		// Call to subsystem addref
	}
	
	static void release(T* obj)
	{
		// Call to subsystem release
	}
	
	std::string name;
	asIScriptEngine* engine;
	
};

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