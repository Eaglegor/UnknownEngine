#include <Parsers/AssimpMeshDataProviderDescParser.h>
#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Loader
	{
		
		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
		typedef boost::optional<const std::string&> OptionalStringOption;
		
		namespace GLOBAL_OPTIONS
		{
			const std::string FILENAME = "filename"; // required
			const std::string LOG_LEVEL = "log_level"; // optional
		}
		
		namespace POSTPROCESSING
		{
			const std::string SECTION_NAME = "Postprocessing"; // optional
			
			namespace OPTIONS
			{
				const std::string GENERATE_NORMALS = "generate_normals"; // optional
				const std::string GENERATE_TANGENTS = "generate_tangents"; // optional
				const std::string TRIANGULATE = "triangulate"; // optional
			}
		}
		
		AssimpMeshDataProvider::Descriptor AssimpMeshDataProviderDescParser::parse ( const Core::Properties& props )
		{
			AssimpMeshDataProvider::Descriptor desc;
			
			desc.filename = props.get<std::string>(GLOBAL_OPTIONS::FILENAME);
			
			OptionalOptionsSection postprocessing_section = props.get_optional<Core::Properties>(POSTPROCESSING::SECTION_NAME);
			if(postprocessing_section.is_initialized())
			{
				OptionalStringOption generate_normals = postprocessing_section->get_optional<std::string>(POSTPROCESSING::OPTIONS::GENERATE_NORMALS);
				if(generate_normals.is_initialized()) desc.postprocessing.generate_normals = boost::lexical_cast<bool>(generate_normals.get());
				
				OptionalStringOption generate_tangents = postprocessing_section->get_optional<std::string>(POSTPROCESSING::OPTIONS::GENERATE_TANGENTS);
				if(generate_tangents.is_initialized()) desc.postprocessing.generate_tangents = boost::lexical_cast<bool>(generate_tangents.get());
				
				OptionalStringOption triangulate = postprocessing_section->get_optional<std::string>(POSTPROCESSING::OPTIONS::TRIANGULATE);
				if(triangulate.is_initialized()) desc.postprocessing.triangulate = boost::lexical_cast<bool>(triangulate.get());
			}
			
			OptionalStringOption log_level = props.get_optional<std::string>(GLOBAL_OPTIONS::LOG_LEVEL);
			if(log_level.is_initialized()) desc.log_level = Core::LogHelper::parseLogLevel(log_level.get());
			
			return desc;
		}
	}
}