#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <DataProvider/IDataProvider.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class IDataProviderRegistrator : public ClassReferenceTypeRegistrator<Loader::IDataProvider>
		{
				IDataProviderRegistrator ( const std::string& registered_name ):
				ClassReferenceTypeRegistrator<Loader::IDataProvider>(registered_name)
				{}
		};
	}
}