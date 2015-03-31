#pragma once

#include <Descriptors/AngelScriptSubsystemDesc.h>
#include <memory>
#include <unordered_map>

#include <ASIncludes.h>
#include <typeinfo>
#include <typeindex>

namespace UnknownEngine
{
	
	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Behavior
	{
		class ITypeRegistrator;
		class AngelScriptSubsystem
		{
		public:
			AngelScriptSubsystem(const std::string& name, const AngelScriptSubsystemDesc& desc, Core::EngineContext* engine_context);
			~AngelScriptSubsystem();

			void init();
			void shutdown();

			asIScriptEngine* getScriptEngine();

			template<typename T>
			void typeNameIsBound()
			{
				return type_name_bindings.find(std::type_index(typeid(T))) != type_name_bindings.end();
			}

			template<typename T>
			void bindTypeName(const char* name)
			{
				type_name_bindings.emplace(std::type_index(typeid(T)), name);
			};
			
			template<typename T>
			const char* getTypeName()
			{
				auto iter = type_name_bindings.find(std::type_index(typeid(T)));
				if(iter == type_name_bindings.end())
				{
					return "???";
				}
				return iter->second.c_str();
			};

		private:
			void registerDefaultTemplatesPredefinition();
			void registerStandardTypes();
			void registerObjectType(const ITypeRegistrator& registrator);
			void registerMessageType(const ITypeRegistrator& registrator);
			
			std::string name;
			Core::ILogger* logger;
			
			Core::EngineContext* engine_context;
			AngelScriptSubsystemDesc desc;

			asIScriptEngine *script_engine;
			
			std::unordered_map<std::string, asIScriptModule*> modules;

			std::unordered_map<std::type_info, std::string> type_name_bindings;

			std::unordered_map<void*, size_t> references_counters;
		};
	}
}
