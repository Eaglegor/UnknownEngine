#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <NameGenerators/NameGenerator.h>
#include <Registrators/Utils/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class NameGeneratorRegistrator : public ClassReferenceTypeRegistrator<Utils::NameGenerator>
		{
		public:
			NameGeneratorRegistrator() :
				ClassReferenceTypeRegistrator<Utils::NameGenerator>("NameGenerator", UTILS_AS_NAMESPACE_NAME)
			{}

		protected:
			bool registerMethods(asIScriptEngine* script_engine) const override
			{
				int result = script_engine->RegisterObjectMethod(getRegisteredName(), "std::string generateName()", asMETHOD(class_type, generateName), asCALL_THISCALL);
				if (result < 0) return false;

				return true;
			}

		};
	}
}