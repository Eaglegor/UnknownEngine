#pragma once
#include <DataProviders/AssimpMeshDataProvider.h>
#include <Parsers/AssimpMeshDataProviderDescParser.h>
#include <DescriptorContainer.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Loader
	{
		class AssimpMeshDataProviderDescriptorGetter : public boost::static_visitor<AssimpMeshDataProvider::Descriptor>
		{
		public:
			
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDescriptorProvided);
			
			AssimpMeshDataProvider::Descriptor operator()(const Core::DescriptorContainer& descriptor_container)
			{
				if(descriptor_container.isEmpty()) throw NoDescriptorProvided("Can't find descriptor for data provider");
				return descriptor_container.get<AssimpMeshDataProvider::Descriptor>();
			}
			
			AssimpMeshDataProvider::Descriptor operator()(const Core::Properties &creation_options)
			{
				return AssimpMeshDataProviderDescParser::parse(creation_options);
			}
		};
	}
}