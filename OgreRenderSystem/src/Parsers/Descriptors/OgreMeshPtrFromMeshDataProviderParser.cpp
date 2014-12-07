#include <stdafx.h>

#include <Parsers/Descriptors/OgreMeshPtrFromMeshDataProviderDescriptorParser.h>
#include <Properties/PropertiesTree.h>
#include <Logging.h>
#include <CommonParsers/PropertiesParser.h>

namespace UnknownEngine {
	namespace Graphics {

		typedef OgreMeshPtrFromMeshDataProviderDescriptor DescriptorType;
		
		DescriptorType OgreMeshPtrFromMeshDataProviderDescriptorParser::parse( const UnknownEngine::Core::Properties& props )
		{
			DescriptorType desc;

			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				props,
				{
					{"mesh_data_provider", PropertiesParser::OptionalRawValue<Core::IDataProvider*>(desc.mesh_data_provider)},
					{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity>(desc.log_level)},
				}
			);

			return desc;
		}
		
	}	
}