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
			
			virtual bool registerMethods ( asIScriptEngine* script_engine ) const
			{
				int result;
				result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::IDataProvider@ createDataProvider(const Core::DataProviderDesc &in)", asMETHOD(Core::ResourceManager, createDataProvider), asCALL_THISCALL);
				if(result < 0) return false;
				
				return true;
			}
			
		};
	}
}