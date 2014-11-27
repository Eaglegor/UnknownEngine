#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <DataProvider/IDataProvider.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class IDataProviderRegistrator : public ClassReferenceTypeRegistrator<Loader::IDataProvider>
		{
		public:
			IDataProviderRegistrator(const std::string& registered_name, const std::string& declaration_namespace = "") :
				ClassReferenceTypeRegistrator<Loader::IDataProvider>(registered_name, declaration_namespace)
			{}

		protected:
			bool registerMethods(asIScriptEngine* script_engine) const override
			{
				int result = script_engine->RegisterObjectMethod(registered_name.c_str(), "void reserve()", asMETHOD(Loader::IDataProvider, reserve), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(registered_name.c_str(), "void release()", asMETHOD(Loader::IDataProvider, release), asCALL_THISCALL);
				if (result < 0) return false;

				return true;
			}

		};
	}
}