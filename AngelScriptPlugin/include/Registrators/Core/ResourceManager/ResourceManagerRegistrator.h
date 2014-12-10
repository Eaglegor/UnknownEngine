#pragma once

#include <ResourceManager/ResourceManager.h>
#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ResourceManagerRegistrator : public ClassReferenceTypeRegistrator<Core::ResourceManager>
		{
		public:
			ResourceManagerRegistrator():
			ClassReferenceTypeRegistrator< Core::ResourceManager >("ResourceManager", CORE_AS_NAMESPACE_NAME)
			{}
			
		protected:
			
			static Core::IDataProvider* create_data_provider(const Core::DataProviderDesc &desc)
			{
				return CREATE_DATA_PROVIDER(desc);
			}
			
			static Core::IDataProvider* get_data_provider(const std::string &name)
			{
				return GET_DATA_PROVIDER(name.c_str());
			}
			
			static void release_data_provider(Core::IDataProvider* data_provider)
			{
				return RELEASE_DATA_PROVIDER(data_provider);
			}
			
			virtual bool registerMethods ( asIScriptEngine* script_engine ) const
			{
				int result;
				result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::IDataProvider@ createDataProvider(const Core::DataProviderDesc &in)", asMETHOD(Core::ResourceManager, createDataProvider), asCALL_THISCALL);
				if(result < 0) return false;
				
				script_engine->SetDefaultNamespace("");
				result = script_engine->RegisterGlobalFunction("Core::IDataProvider@ CREATE_DATA_PROVIDER(const Core::DataProviderDesc &in)", asFUNCTION(ResourceManagerRegistrator::create_data_provider), asCALL_CDECL);
				if(result < 0) return false;
				
				result = script_engine->RegisterGlobalFunction("Core::IDataProvider@ GET_DATA_PROVIDER(const std::string &in)", asFUNCTION(ResourceManagerRegistrator::get_data_provider), asCALL_CDECL);
				if(result < 0) return false;
				
				result = script_engine->RegisterGlobalFunction("void RELEASE_DATA_PROVIDER(Core::IDataProvider@)", asFUNCTION(ResourceManagerRegistrator::release_data_provider), asCALL_CDECL);
				if(result < 0) return false;
				script_engine->SetDefaultNamespace(CORE_AS_NAMESPACE_NAME.c_str());
				
				return true;
			}
			
		};
	}
}