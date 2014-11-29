#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <DataProvider/IDataProvider.h>
#include <Registrators/Loader/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class IDataProviderRegistrator : public ClassReferenceTypeRegistrator<Loader::IDataProvider>
		{
		public:
			IDataProviderRegistrator() :
				ClassReferenceTypeRegistrator<Loader::IDataProvider>("IDataProvider", LOADER_AS_NAMESPACE_NAME)
			{}

		protected:
			bool registerMethods(asIScriptEngine* script_engine) const override
			{
				int result = script_engine->RegisterObjectMethod(getRegisteredName(), "void reserve()", asMETHOD(class_type, reserve), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void release()", asMETHOD(class_type, release), asCALL_THISCALL);
				if (result < 0) return false;

				return true;
			}

		};
	}
}