#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <ResourceManager/DataProviders/IDataProvider.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class IDataProviderRegistrator : public ClassReferenceTypeRegistrator<Core::IDataProvider>
		{
		public:
			IDataProviderRegistrator() :
				ClassReferenceTypeRegistrator<Core::IDataProvider>("IDataProvider", CORE_AS_NAMESPACE_NAME)
			{}

		protected:
			bool registerMethods(asIScriptEngine* script_engine) const override
			{
				int result;
				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void startLoading()", asMETHOD(Core::IDataProvider, startLoading), asCALL_THISCALL);
				if (result < 0) return false;
				
				return true;
			}

		};
	}
}