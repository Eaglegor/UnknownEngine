#pragma once

#include <DataProviders/OgreMeshPtrProvider.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreMeshPtrFromMeshDataProvider : public OgreMeshPtrProvider
		{
			public:

				struct Descriptor
				{
					Loader::IDataProvider* mesh_data_provider;
				};

				OgreMeshPtrFromMeshDataProvider ( const std::string &name, const Descriptor &descriptor );
			protected:
				virtual void internalLoad ( Loader::ResourceContainer &out_container );
				Loader::IDataProvider* mesh_data_provider;
		};

	} // namespace Graphics
} // namespace UnknownEngine
