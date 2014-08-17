#include <Parsers/Descriptors/OgreMeshPtrFromMeshDataProviderDescriptorParser.h>
#include <Properties/PropertiesTree.h>
#include <LogHelper.h>

namespace UnknownEngine {
	namespace Graphics {
		
		namespace GLOBAL_OPTIONS
		{
			const std::string MESH_DATA_PROVIDER = "mesh_data_provider";
			const std::string LOG_LEVEL = "log_level";
		};

		typedef OgreMeshPtrFromMeshDataProvider::Descriptor DescriptorType;
		
		DescriptorType OgreMeshPtrFromMeshDataProviderDescriptorParser::parse( const UnknownEngine::Core::Properties& props )
		{
			DescriptorType desc;
			
			const boost::optional<Loader::IDataProvider* const&> mesh_data_provider = props.get_optional<Loader::IDataProvider*>(GLOBAL_OPTIONS::MESH_DATA_PROVIDER);
			if(mesh_data_provider.is_initialized()) 
			{
				desc.mesh_data_provider = mesh_data_provider.get();
			}
			
			boost::optional<const std::string&> log_level = props.get_optional<std::string>(GLOBAL_OPTIONS::LOG_LEVEL);
			if(log_level.is_initialized()) 
			{
				desc.log_level = Core::LogHelper::parseLogLevel(log_level.get());
			}
			
			return desc;
		}
		
	}	
}