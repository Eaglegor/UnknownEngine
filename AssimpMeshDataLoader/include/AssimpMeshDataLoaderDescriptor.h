#pragma once
#include <LogSeverity.h>
#include <Descriptors/DescriptorUtils.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Loader
	{
		struct AssimpMeshDataLoaderDescriptor : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			Utils::OptionalProperty<Core::LogSeverity> log_level;
			
			AssimpMeshDataLoaderDescriptor():
			log_level(Core::LogSeverity::NONE)
			{
				UEDESC_ADD_FIELD(log_level);
			}
		};
	}
}