#pragma once

#include <ComponentDesc.h>
#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <Registrators/Core/ComponentSystem/ComponentDescBehaviorWrapper.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ComponentDescRegistrator : public ClassValueTypeRegistrator<Core::ComponentDesc>
		{
			public:
				ComponentDescRegistrator() :
					ClassValueTypeRegistrator< UnknownEngine::Core::ComponentDesc > ( "ComponentDesc", CORE_AS_NAMESPACE_NAME )
				{}

			protected:
				virtual bool registerProperties ( asIScriptEngine* script_engine ) const override
				{
					int result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string name", asOFFSET ( class_type, name ) );
					if ( result < 0 ) return false;

					result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string type", asOFFSET ( class_type, type ) );
					if ( result < 0 ) return false;
					
					result = script_engine->RegisterObjectMethod ( getRegisteredName(), "Core::Properties& get_descriptor()", asFUNCTION(ComponentDescBehaviorWrapper::get_descriptor), asCALL_CDECL_OBJFIRST );
					if ( result < 0 ) return false;
					
					result = script_engine->RegisterObjectMethod ( getRegisteredName(), "void set_descriptor(Core::Properties &in)", asFUNCTION(ComponentDescBehaviorWrapper::set_descriptor), asCALL_CDECL_OBJFIRST );
					if ( result < 0 ) return false;
					
					return true;
				}
		};
	}
}
