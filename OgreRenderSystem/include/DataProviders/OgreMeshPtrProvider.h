#pragma once

#include <DataProvider/LazyLoadDataProvider.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreMeshPtrProvider : public Loader::LazyLoadDataProvider
		{
			public:
				explicit OgreMeshPtrProvider ( const std::string &name ) : Loader::LazyLoadDataProvider(name)
				{}

				virtual ~OgreMeshPtrProvider() {};
		};
	}
}
