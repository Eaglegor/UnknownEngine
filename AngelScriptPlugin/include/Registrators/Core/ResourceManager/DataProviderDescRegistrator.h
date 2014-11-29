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
				virtual bool registerProperties ( asIScriptEngine* script_engine ) const override
				{
					int result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string name", asOFFSET ( class_type, name ) );
					if ( result < 0 ) return false;

					result = script_engine->RegisterObjectProperty ( getRegisteredName(), "std::string type", asOFFSET ( class_type, type ) );
					if ( result < 0 ) return false;
					
					return true;
				}
		};
	}
}
