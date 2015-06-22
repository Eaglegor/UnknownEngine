#pragma once

#include <string>
#include <Descriptors/Schemas/DescriptorSchema.h>
#include <Descriptors/Schemas/BaseDescriptorSchema.h>
#include <ResourceLoaders/AssimpMeshDataLoaderDesc.h>

namespace UnknownEngine
{
	namespace Utils
	{
		typedef Resources::AssimpMeshDataProviderDesc::PostprocessingDesc AssimpLoaderPostprocessingDesc;

		template<>
		class DescriptorSchema<AssimpLoaderPostprocessingDesc> :
				public BaseDescriptorSchema<AssimpLoaderPostprocessingDesc>
		{
			public:
				DescriptorSchema()
				{
					addField<bool>("generate_tangents", [](AssimpLoaderPostprocessingDesc &c, const bool &value){c.generate_tangents = value;}, true);
					addField<bool>("generate_normals", [](AssimpLoaderPostprocessingDesc &c, const bool &value){c.generate_normals = value;}, true);
					addField<bool>("triangulate", [](AssimpLoaderPostprocessingDesc &c, const bool &value){c.triangulate = value;}, true);
					addField<bool>("flip_texture_coordinates", [](AssimpLoaderPostprocessingDesc &c, const bool &value){c.flip_texture_coordinates = value;}, true);
				}
		};

		typedef Resources::AssimpMeshDataProviderDesc AssimpLoaderDesc;

		template<>
		class DescriptorSchema<AssimpLoaderDesc> :
				public BaseDescriptorSchema<AssimpLoaderDesc>
		{
			public:
				DescriptorSchema()
				{
					addField<bool>("postprocessing", [](AssimpLoaderDesc &c, const AssimpLoaderPostprocessingDesc &value){c.postprocessing = value;}, true);
					addField<bool>("filename", [](AssimpLoaderDesc &c, const std::string &value){c.filename = value;}, true);
				}
		};
	}

}

