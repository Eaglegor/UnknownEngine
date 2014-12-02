#pragma once

#include <DataProvider/DataProviderDesc.h>
#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Loader/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class DataProviderDescRegistrator : public ClassValueTypeRegistrator<Loader::DataProviderDesc>
		{
			public:
				DataProviderDescRegistrator() :
					ClassValueTypeRegistrator< Loader::DataProviderDesc > ( "DataProviderDesc", LOADER_AS_NAMESPACE_NAME )
				{}

			protected:
				static Core::Properties& get_descriptor(Loader::DataProviderDesc* this_ptr)
				{
					return boost::get<Core::Properties>(this_ptr->descriptor);
				}
				
				static void set_descriptor(Loader::DataProviderDesc* this_ptr, Core::Properties &value)
				{
					this_ptr->descriptor = value;
				}
				
				virtual bool registerProperties ( asIScriptEngine* script_engine ) const override
				{
					int result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string name", asOFFSET ( Loader::DataProviderDesc, name ) );
					if ( result < 0 ) return false;

					result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string type", asOFFSET ( Loader::DataProviderDesc, type ) );
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
