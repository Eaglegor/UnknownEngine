#pragma once

#include <ComponentDesc.h>
#include <Registrators/ClassValueTypeRegistrator.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ComponentDescRegistrator : public ClassValueTypeRegistrator<Core::ComponentDesc>
		{
			public:
				ComponentDescRegistrator(const std::string& registered_name, const std::string& declaration_namespace = "") :
					ClassValueTypeRegistrator< UnknownEngine::Core::ComponentDesc > ( registered_name, declaration_namespace )
				{}

			protected:
				virtual bool registerProperties ( asIScriptEngine* script_engine ) const override
				{
					int result = script_engine->RegisterObjectProperty ( registered_name.c_str(), "string name", asOFFSET ( Core::ComponentDesc, name ) );
					if ( result < 0 ) return false;

					result = script_engine->RegisterObjectProperty ( registered_name.c_str(), "string type", asOFFSET ( Core::ComponentDesc, type ) );
					if ( result < 0 ) return false;
					
					return true;
				}
		};
	}
}
