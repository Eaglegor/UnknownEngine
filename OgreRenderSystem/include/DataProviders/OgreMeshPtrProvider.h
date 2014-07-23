#pragma once

#include <DataProvider/SeparateLoaderThreadDataProvider.h>

namespace UnknownEngine {
	namespace Graphics {

		class OgreMeshPtrProvider : public UnknownEngine::Loader::SeparateLoaderThreadDataProvider
		{
			public:
				OgreMeshPtrProvider();
			protected:
				virtual void internalLoad(Loader::ResourceContainer &out_container);
		};

	} // namespace Graphics
} // namespace UnknownEngine
