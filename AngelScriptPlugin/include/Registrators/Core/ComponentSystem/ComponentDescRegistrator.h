#pragma once

#include <ComponentSystem/ComponentDesc.h>
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
				static Core::Properties& get_descriptor(Core::ComponentDesc* this_ptr)
				{
					return boost::get<Core::Properties>(this_ptr->descriptor);
				}
				
				static void set_descriptor(Core::ComponentDesc* this_ptr, Core::Properties &value)
				{
					this_ptr->descriptor = value;
				}
				
				virtual bool registerProperties ( asIScriptEngine* script_engine ) const override
				{
					int result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string name", asOFFSET ( Core::ComponentDesc, name ) );
					if ( result < 0 ) return false;

					result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string type", asOFFSET ( Core::ComponentDesc, type ) );
					if ( result < 0 ) return false;
					
					result = script_engine->RegisterObjectMethod ( getRegisteredName(), "Core::Properties& get_descriptor()", asFUNCTION(ComponentDescRegistrator::get_descriptor), asCALL_CDECL_OBJFIRST );
					if ( result < 0 ) return false;
					
					result = script_engine->RegisterObjectMethod ( getRegisteredName(), "void set_descriptor(Core::Properties &in)", asFUNCTION(ComponentDescRegistrator::set_descriptor), asCALL_CDECL_OBJFIRST );
					if ( result < 0 ) return false;
					
					return true;
				}
		};
	}
}
