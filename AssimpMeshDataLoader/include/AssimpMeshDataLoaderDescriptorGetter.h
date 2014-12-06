#pragma once
#include <boost/variant/static_visitor.hpp>
#include <AssimpMeshDataLoaderDescriptor.h>
#include <DescriptorContainer.h>
#include <Logging.h>
#include <CommonParsers/PropertiesParser.h>

namespace UnknownEngine
{
	namespace Loader
	{
		class AssimpMeshDataLoaderDescriptorGetter : public boost::static_visitor<AssimpMeshDataLoaderDescriptor>
		{
		public:
			
			AssimpMeshDataLoaderDescriptor operator()(const Core::DescriptorContainer& descriptor_container) const
			{
				if(descriptor_container.isEmpty()) return AssimpMeshDataLoaderDescriptor();
				return descriptor_container.get<AssimpMeshDataLoaderDescriptor>();
			}
			
			AssimpMeshDataLoaderDescriptor operator()(const Core::Properties& creation_options) const
			{
				AssimpMeshDataLoaderDescriptor desc;
				
				using Utils::PropertiesParser;
				
				PropertiesParser::parse
				(
					creation_options,
					{
						{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity>(desc.log_level)}
					}
				);
				
				return desc;
			}
		};
	}
}