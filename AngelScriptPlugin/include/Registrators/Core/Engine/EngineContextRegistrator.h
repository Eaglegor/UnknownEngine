#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <EngineContext.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class EngineContextRegistrator : public ClassReferenceTypeRegistrator<Core::EngineContext>
		{
			public:
				EngineContextRegistrator() :
					ClassReferenceTypeRegistrator< Core::EngineContext > ( "EngineContext", CORE_AS_NAMESPACE_NAME )
				{}
				
				virtual bool registerMethods ( asIScriptEngine* script_engine ) const
				{
					int result;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::ComponentsManager@ getComponentsManager()", asMETHOD(Core::EngineContext, getComponentsManager), asCALL_THISCALL);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::ResourceManager@ getResourceManager()", asMETHOD(Core::EngineContext, getResourceManager), asCALL_THISCALL);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::MessageDispatcher@ getMessageDispatcher()", asMETHOD(Core::EngineContext, getMessageDispatcher), asCALL_THISCALL);
					if(result < 0) return false;
					
					return true;
				}
		};
	}
}
