#pragma once

#include <LogSeverity.h>
#include <Descriptors/DescriptorUtils.h>

namespace UnknownEngine
{
	namespace Loader
	{
		struct AssimpMeshDataProviderDesc : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			struct PostprocessingDesc : public Utils::Descriptor
			{
				using Utils::Descriptor::operator=;
				
				Utils::OptionalProperty<bool> generate_tangents;
				Utils::OptionalProperty<bool> generate_normals;
				Utils::OptionalProperty<bool> triangulate;
				Utils::OptionalProperty<bool> flip_texture_coordinates;
				
				PostprocessingDesc():
				generate_tangents(false),
				generate_normals(false),
				triangulate(false),
				flip_texture_coordinates(false)
				{
					UEDESC_ADD_FIELD(generate_tangents);
					UEDESC_ADD_FIELD(generate_normals);
					UEDESC_ADD_FIELD(triangulate);
					UEDESC_ADD_FIELD(flip_texture_coordinates);
				}
			
			};
			
			Utils::OptionalDescriptor<PostprocessingDesc> postprocessing;
			
			Utils::OptionalProperty<std::string> filename;
			Utils::OptionalProperty<Core::LogSeverity> log_level;
			
			AssimpMeshDataProviderDesc():
			log_level(Core::LogSeverity::NONE)
			{
				UEDESC_ADD_NESTED_DESCRIPTOR(postprocessing);
				UEDESC_ADD_FIELD(filename);
				UEDESC_ADD_FIELD(log_level);
			};
		};
	}
}
			
			