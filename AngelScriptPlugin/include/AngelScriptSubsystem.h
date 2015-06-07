#pragma once

#include <Descriptors/AngelScriptSubsystemDesc.h>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include <ASIncludes.h>
#include <mutex>
#include <ASBind/TypeInfo.h>

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
			bool typeInfoIsBound()
			{
				return type_info_bindings.find(typeid(T).name()) != type_info_bindings.end();
			}

			template<typename T>
			void bindTypeInfo(const char* name, ASBind::ClassType type)
			{
				ASBind::TypeInfo info;
				info.type = type;
				info.name = name;
				type_info_bindings.emplace(typeid(T).name(), info);
			};
			
			template<typename T>
			ASBind::TypeInfo getTypeInfo()
			{
				auto iter = type_info_bindings.find(typeid(T).name());
				if(iter == type_info_bindings.end())
				{
					ASBind::TypeInfo info;
					info.name = "???";
					info.type = ASBind::ClassType::UNREGISTERED_TYPE;
					return info;
				}
				return iter->second;
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

			std::unordered_map<std::string, ASBind::TypeInfo> type_info_bindings;
		};
	}
}
