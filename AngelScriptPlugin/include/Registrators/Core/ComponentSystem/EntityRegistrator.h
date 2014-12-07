#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <ComponentSystem/Entity.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class EntityRegistrator : public ClassReferenceTypeRegistrator<Core::IEntity>
		{
			public:
				EntityRegistrator() :
					ClassReferenceTypeRegistrator< Core::IEntity > ( "Entity", CORE_AS_NAMESPACE_NAME )
				{}

			protected:
				virtual bool registerMethods(asIScriptEngine* script_engine) const override
				{
					int result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::IComponent@ createComponent(const ComponentDesc &in)", asMETHOD(Core::IEntity, createComponent), asCALL_THISCALL);
					if (result < 0) return false;

					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void removeComponent(Core::IComponent@)", asMETHOD(Core::IEntity, removeComponent), asCALL_THISCALL);
					if (result < 0) return false;

					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void removeAllComponents()", asMETHOD(Core::IEntity, removeAllComponents), asCALL_THISCALL);
					if (result < 0) return false;

					return true;
				}
				
		};
	}
}
