#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <ComponentSystem/ComponentDesc.h>
#include <ComponentSystem/ComponentsManager.h>
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
				int result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::Entity@ createEntity(const std::string &in)", asMETHOD(Core::ComponentsManager, createEntity), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void removeEntity(Core::Entity @)", asMETHOD(Core::ComponentsManager, removeEntity), asCALL_THISCALL);
				if (result < 0) return false;

				result = script_engine->RegisterObjectMethod(getRegisteredName(), "Utils::NameGenerator@ getNameGenerator()", asMETHOD(Core::ComponentsManager, getNameGenerator), asCALL_THISCALL);
				if (result < 0) return false;

				return true;
			}

		};
	}
}