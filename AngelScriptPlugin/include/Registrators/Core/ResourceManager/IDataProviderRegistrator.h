#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <ResourceManager/DataProviders/IDataProvider.h>
#include <Registrators/Loader/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class IDataProviderRegistrator : public ClassReferenceTypeRegistrator<Core::IDataProvider>
		{
		public:
			IDataProviderRegistrator() :
				ClassReferenceTypeRegistrator<Core::IDataProvider>("IDataProvider", LOADER_AS_NAMESPACE_NAME)
			{}

		protected:
			bool registerMethods(asIScriptEngine* script_engine) const override
			{
				int result = script_engine->RegisterObjectMethod(getRegisteredName(), "void reserve()", asMETHOD(Core::IDataProvider, reserve), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void release()", asMETHOD(Core::IDataProvider, release), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void startLoading()", asMETHOD(Core::IDataProvider, startLoading), asCALL_THISCALL);
				if (result < 0) return false;
				
				return true;
			}

		};
	}
}