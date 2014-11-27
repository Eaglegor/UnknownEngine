#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <ComponentDesc.h>
#include <ComponentsManager.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ComponentsManagerRegistrator : public ClassReferenceTypeRegistrator<Core::ComponentsManager>
		{
		public:
			ComponentsManagerRegistrator() :
				ClassReferenceTypeRegistrator<Core::ComponentsManager>("ComponentsManager", CORE_AS_NAMESPACE_NAME)
			{}

		protected:
			bool registerMethods(asIScriptEngine* script_engine) const override
			{
				int result = script_engine->RegisterObjectMethod(registered_name.c_str(), "Core::Entity@ createEntity(const string &in)", asMETHOD(class_type, createEntity), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(registered_name.c_str(), "void removeEntity(Core::Entity @in)", asMETHOD(class_type, removeEntity), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(registered_name.c_str(), "Utils::NameGenerator@ getNameGenerator()", asMETHOD(class_type, getNameGenerator), asCALL_THISCALL);
				if (result < 0) return false;

				return true;
			}

		};
	}
}