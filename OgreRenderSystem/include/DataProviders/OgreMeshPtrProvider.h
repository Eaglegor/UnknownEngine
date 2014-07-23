#pragma once

#include <DataProvider/SeparateLoaderThreadDataProvider.h>

namespace UnknownEngine {
	namespace Graphics {

		class OgreMeshPtrProvider : public UnknownEngine::Loader::SeparateLoaderThreadDataProvider
		{
			public:

				struct Descriptor
				{
					bool nativeLoad = false;
					Loader::IDataProvider* mesh_data_provider;
				};

				OgreMeshPtrProvider(const std::string &name, const Descriptor &descriptor);
			protected:
				virtual void internalLoad(Loader::ResourceContainer &out_container);
				Loader::IDataProvider* mesh_data_provider;
		};

	} // namespace Graphics
} // namespace UnknownEngine
