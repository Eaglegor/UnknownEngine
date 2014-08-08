#include <stdafx.h>

#include <Parsers/OgreRenderableDescriptorParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <DataProvider/IDataProvider.h>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <LogHelper.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
#define GET_OPTIONAL_OPTIONS_SECTION(section_name) properties.get_optional<Core::Properties>(section_name);
#define OVERRIDE_DEFAULT_VALUE(config_section, option_name, output_field) output_field = config_section->get<std::string>(option_name, output_field);

		namespace MATERIAL_SECTION
		{
			const std::string SECTION_NAME = "Material";

			namespace OPTIONS
			{
				const std::string MATERIAL_NAME = "material_name";
			}
		}

		namespace GLOBAL_OPTIONS
		{
			const std::string MESH_PTR_PROVIDER = "mesh_ptr_provider";
			const std::string LOG_LEVEL = "log_level";
		}

		namespace INITIAL_TRANSFORM_SECTION
		{
			const std::string SECTION_NAME = "InitialTransform";

			namespace OPTIONS
			{
				const std::string POSITION = "position";
				const std::string ORIENTATION = "orientation_quat";
			}
		}

		OgreRenderableComponent::Descriptor OgreRenderableDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreRenderableComponent::Descriptor desc;

			OptionalOptionsSection material_section = GET_OPTIONAL_OPTIONS_SECTION ( MATERIAL_SECTION::SECTION_NAME );
			if ( material_section.is_initialized() )
			{
				OVERRIDE_DEFAULT_VALUE ( material_section, MATERIAL_SECTION::OPTIONS::MATERIAL_NAME, desc.material_name );
			}

			OptionalOptionsSection initial_transform_section = GET_OPTIONAL_OPTIONS_SECTION ( INITIAL_TRANSFORM_SECTION::SECTION_NAME );
			if ( initial_transform_section.is_initialized() )
			{
				boost::optional<const std::string&> initial_position = initial_transform_section->get_optional<std::string> ( INITIAL_TRANSFORM_SECTION::OPTIONS::POSITION );
				if ( initial_position.is_initialized() ) desc.initial_transform.setPosition ( Utils::Vector3Parser::parse ( initial_position.get() ) );

				boost::optional<const std::string&> initial_orientation_quat = initial_transform_section->get_optional<std::string> ( INITIAL_TRANSFORM_SECTION::OPTIONS::ORIENTATION );
				if ( initial_orientation_quat.is_initialized() ) desc.initial_transform.setOrientation ( Utils::QuaternionParser::parse ( initial_orientation_quat.get() ) );
			}
			
			boost::optional<const std::string&> log_level = properties.get_optional<std::string>(GLOBAL_OPTIONS::LOG_LEVEL);
			if(log_level.is_initialized())
			{
				desc.log_level = Core::LogHelper::parseLogLevel(log_level.get());
			}

			Loader::IDataProvider* data_provider = properties.get<Loader::IDataProvider*> ( GLOBAL_OPTIONS::MESH_PTR_PROVIDER, nullptr );
			OgreMeshPtrProvider* mesh_ptr_provider = dynamic_cast<OgreMeshPtrProvider*> ( data_provider );
			desc.mesh_data_provider = mesh_ptr_provider;

			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
