#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <NameGenerators/NameGenerator.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class NameGeneratorRegistrator : public ClassReferenceTypeRegistrator<Utils::NameGenerator>
		{
		public:
			NameGeneratorRegistrator(const std::string &registered_name, const std::string& declaration_namespace = "") :
				ClassReferenceTypeRegistrator<Utils::NameGenerator>(registered_name, declaration_namespace)
			{}

		protected:
			bool registerMethods(asIScriptEngine* script_engine) const override
			{
				int result = script_engine->RegisterObjectMethod(registered_name.c_str(), "string generateName()", asMETHOD(Utils::NameGenerator, generateName), asCALL_THISCALL);
				if (result < 0) return false;

				return true;
			}

		};
	}
}