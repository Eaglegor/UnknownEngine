#pragma once

#include <ResourceManager/DataProviders/LazyLoadDataProvider.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreMeshPtrProvider : public Core::LazyLoadDataProvider
		{
			public:
				explicit OgreMeshPtrProvider ( const std::string &name ) : Core::LazyLoadDataProvider(name)
				{}

				virtual ~OgreMeshPtrProvider() {};
		};
	}
}
