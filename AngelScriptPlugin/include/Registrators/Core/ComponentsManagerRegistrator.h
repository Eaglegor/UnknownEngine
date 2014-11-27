#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <ComponentDesc.h>
#include <ComponentsManager.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ComponentsManagerRegistrator : public ClassReferenceTypeRegistrator<Core::ComponentsManager>
		{
		public:
			ComponentsManagerRegistrator(const std::string &registered_name, const std::string& declaration_namespace = "") :
				ClassReferenceTypeRegistrator<Core::ComponentsManager>(registered_name, declaration_namespace)
			{}

		protected:
			bool registerMethods(asIScriptEngine* script_engine) const override
			{
				int result = script_engine->RegisterObjectMethod(registered_name.c_str(), "Core::Entity@ createEntity(const string &in)", asMETHOD(Core::ComponentsManager, createEntity), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(registered_name.c_str(), "void removeEntity(Core::Entity @in)", asMETHOD(Core::ComponentsManager, removeEntity), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(registered_name.c_str(), "Utils::NameGenerator@ getNameGenerator()", asMETHOD(Core::ComponentsManager, getNameGenerator), asCALL_THISCALL);
				if (result < 0) return false;

				return true;
			}

		};
	}
}