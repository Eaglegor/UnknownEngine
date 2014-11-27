#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <Objects/Entity.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class EntityRegistrator : public ClassReferenceTypeRegistrator<Core::Entity>
		{
			public:
				EntityRegistrator(const std::string& registered_name, const std::string& declaration_namespace = "") :
					ClassReferenceTypeRegistrator< Core::Entity > ( registered_name, declaration_namespace )
				{}

			protected:
				virtual bool registerMethods(asIScriptEngine* script_engine) const override
				{
					int result = script_engine->RegisterObjectMethod(registered_name.c_str(), "IComponent@ createComponent(const ComponentDesc &in)", asMETHOD(Core::Entity, createComponent), asCALL_THISCALL);
					if (result < 0) return false;

					result = script_engine->RegisterObjectMethod(registered_name.c_str(), "void removeComponent(IComponent @in)", asMETHOD(Core::Entity, removeComponent), asCALL_THISCALL);
					if (result < 0) return false;

					result = script_engine->RegisterObjectMethod(registered_name.c_str(), "void removeAllComponents()", asMETHOD(Core::Entity, removeAllComponents), asCALL_THISCALL);
					if (result < 0) return false;

					return true;
				}
				
		};
	}
}
