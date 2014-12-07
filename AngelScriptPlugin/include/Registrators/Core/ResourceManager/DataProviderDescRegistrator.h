#pragma once

#include <ResourceManager/DataProviders/DataProviderDesc.h>
#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class DataProviderDescRegistrator : public ClassValueTypeRegistrator<Core::DataProviderDesc>
		{
			public:
				DataProviderDescRegistrator() :
					ClassValueTypeRegistrator< Core::DataProviderDesc > ( "DataProviderDesc", CORE_AS_NAMESPACE_NAME )
				{}

			protected:
				static Core::Properties& get_descriptor(Core::DataProviderDesc* this_ptr)
				{
					return boost::get<Core::Properties>(this_ptr->descriptor);
				}
				
				static void set_descriptor(Core::DataProviderDesc* this_ptr, Core::Properties &value)
				{
					this_ptr->descriptor = value;
				}
				
				virtual bool registerProperties ( asIScriptEngine* script_engine ) const override
				{
					int result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string name", asOFFSET ( Core::DataProviderDesc, name ) );
					if ( result < 0 ) return false;

					result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string type", asOFFSET ( Core::DataProviderDesc, type ) );
					if ( result < 0 ) return false;
					
					result = script_engine->RegisterObjectMethod ( getRegisteredName(), "Core::Properties &get_descriptor()", asFUNCTION ( DataProviderDescRegistrator::get_descriptor ), asCALL_CDECL_OBJFIRST  );
					if ( result < 0 ) return false;
					
					result = script_engine->RegisterObjectMethod ( getRegisteredName(), "void set_descriptor(const Core::Properties&in)", asFUNCTION ( DataProviderDescRegistrator::set_descriptor ), asCALL_CDECL_OBJFIRST  );
					if ( result < 0 ) return false;
					
					return true;
				}
		};
	}
}
