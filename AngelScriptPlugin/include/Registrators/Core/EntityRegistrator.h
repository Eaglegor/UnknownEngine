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
					int result = script_engine->RegisterObjectMethod(registered_name.c_str(), "IComponent@ createComponent(const ComponentDesc &in)", asMETHOD(class_type, createComponent), asCALL_THISCALL);
					if (result < 0) return false;

					result = script_engine->RegisterObjectMethod(registered_name.c_str(), "void removeComponent(IComponent @in)", asMETHOD(class_type, removeComponent), asCALL_THISCALL);
					if (result < 0) return false;

					result = script_engine->RegisterObjectMethod(registered_name.c_str(), "void removeAllComponents()", asMETHOD(class_type, removeAllComponents), asCALL_THISCALL);
					if (result < 0) return false;

					return true;
				}
				
		};
	}
}
