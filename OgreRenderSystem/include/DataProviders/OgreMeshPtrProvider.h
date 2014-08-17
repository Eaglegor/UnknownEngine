#pragma once

#include <DataProvider/SeparateLoaderThreadDataProvider.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreMeshPtrProvider : public Loader::ReferencesCountingDataProvider
		{
			public:
				explicit OgreMeshPtrProvider ( const std::string &name ) : Loader::ReferencesCountingDataProvider(name)
				{}

				virtual void startLoading(){};
				
				virtual ~OgreMeshPtrProvider() {};
		};
	}
}
