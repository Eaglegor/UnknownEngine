#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <Objects/Entity.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class EntityRegistrator : public ClassReferenceTypeRegistrator<Core::Entity>
		{
			public:
				EntityRegistrator() :
					ClassReferenceTypeRegistrator< Core::Entity > ( "Entity", CORE_AS_NAMESPACE_NAME )
				{}

			protected:
				virtual bool registerMethods(asIScriptEngine* script_engine) const override
				{
					int result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::IComponent@ createComponent(const ComponentDesc &in)", asMETHOD(Core::Entity, createComponent), asCALL_THISCALL);
					if (result < 0) return false;

					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void removeComponent(Core::IComponent@)", asMETHOD(Core::Entity, removeComponent), asCALL_THISCALL);
					if (result < 0) return false;

					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void removeAllComponents()", asMETHOD(Core::Entity, removeAllComponents), asCALL_THISCALL);
					if (result < 0) return false;

					return true;
				}
				
		};
	}
}