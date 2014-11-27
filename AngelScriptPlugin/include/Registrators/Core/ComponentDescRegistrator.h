#pragma once

#include <ComponentDesc.h>
#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>

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
					int result = script_engine->RegisterObjectProperty ( registered_name.c_str(), "string name", asOFFSET ( class_type, name ) );
					if ( result < 0 ) return false;

					result = script_engine->RegisterObjectProperty ( registered_name.c_str(), "string type", asOFFSET ( class_type, type ) );
					if ( result < 0 ) return false;
					
					return true;
				}
		};
	}
}
