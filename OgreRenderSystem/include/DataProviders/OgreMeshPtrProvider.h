#pragma once

#include <DataProvider/SeparateLoaderThreadDataProvider.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreMeshPtrProvider : public UnknownEngine::Loader::IDataProvider
		{
			public:
				explicit OgreMeshPtrProvider ( const std::string &name ) : UnknownEngine::Loader::IDataProvider ( name )
				{}

				virtual ~OgreMeshPtrProvider() {};
		};
	}
}
