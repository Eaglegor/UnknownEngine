#include <stdafx.h>

#include <Parsers/Descriptors/OgreRenderableDescriptorParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <DataProvider/IDataProvider.h>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <LogHelper.h>
#include <CommonParsers/LexicalCastForBoolAlpha.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
		typedef boost::optional<const std::string&> OptionalStringOption;

		namespace MATERIAL_SECTION
		{
			const std::string SECTION_NAME = "Material"; // optional

			namespace OPTIONS
			{
				const std::string MATERIAL_NAME = "material_name"; // optional
			}
		}

		namespace GLOBAL_OPTIONS
		{
			const std::string MESH_PTR_PROVIDER = "mesh_ptr_provider"; // required
			const std::string THROW_EXCEPTION_ON_MISSING_MESH_DATA = "throw_exception_on_missing_mesh_data"; // optional
			const std::string LOG_LEVEL = "log_level"; // optional
		}

		namespace INITIAL_TRANSFORM_SECTION
		{
			const std::string SECTION_NAME = "InitialTransform"; // optional
		}

		OgreRenderableComponent::Descriptor OgreRenderableDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreRenderableComponent::Descriptor desc;

			OptionalOptionsSection material_section = properties.get_optional<Core::Properties>( MATERIAL_SECTION::SECTION_NAME );
			if ( material_section.is_initialized() )
			{
				desc.material_desc.name = material_section->get<std::string> ( MATERIAL_SECTION::OPTIONS::MATERIAL_NAME, desc.material_desc.name );
			}

			OptionalOptionsSection initial_transform_section = properties.get_optional<Core::Properties>( INITIAL_TRANSFORM_SECTION::SECTION_NAME );
			if ( initial_transform_section.is_initialized() )
			{
				desc.initial_transform = InitialTransformSectionParser::parse(initial_transform_section.get());
			}
			
			OptionalStringOption log_level = properties.get_optional<std::string>(GLOBAL_OPTIONS::LOG_LEVEL);
			if(log_level.is_initialized())
			{
				desc.log_level = Core::LogHelper::parseLogLevel(log_level.get());
			}

			Loader::IDataProvider* data_provider = properties.get<Loader::IDataProvider*> ( GLOBAL_OPTIONS::MESH_PTR_PROVIDER, nullptr );
			OgreMeshPtrProvider* mesh_ptr_provider = dynamic_cast<OgreMeshPtrProvider*> ( data_provider );
			desc.mesh_data_provider = mesh_ptr_provider;

		
			OptionalStringOption throw_exception_on_missing_mesh_data = properties.get_optional<std::string>( GLOBAL_OPTIONS::THROW_EXCEPTION_ON_MISSING_MESH_DATA );
			if(throw_exception_on_missing_mesh_data.is_initialized()) desc.throw_exception_on_missing_mesh_data = boost::lexical_cast<bool>(throw_exception_on_missing_mesh_data.get());
			
			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
