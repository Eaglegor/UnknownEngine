#include <stdafx.h>

#include <Parsers/Descriptors/OgreRenderableDescriptorParser.h>
#include <Parsers/Sections/InitialTransformSectionParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <DataProvider/IDataProvider.h>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <LogHelper.h>
#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <CommonParsers/PropertiesParser.h>

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

		OgreRenderableComponentDescriptor OgreRenderableDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreRenderableComponentDescriptor desc;

			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				properties,
				{
					{
						"InitialTransform",
						PropertiesParser::ExternalParserOptionalNestedValue<Core::Transform, InitialTransformSectionParser>
						(desc.initial_transform)
					},
					{
						"Material",
						PropertiesParser::OptionalNestedValue
						(
							{
								{"material_name", PropertiesParser::OptionalValue<std::string>( desc.material_desc.name)},
							}
						)
					},
					{"log_level", PropertiesParser::OptionalValue<Utils::LogSeverity>(desc.log_level)},
			 
					{"mesh_ptr_provider", PropertiesParser::RequiredRawValue<Loader::IDataProvider*>( 
						[&](Loader::IDataProvider* data_provider){
							desc.mesh_data_provider = dynamic_cast<OgreMeshPtrProvider*>(data_provider);
						} 
					)},
	
					{"throw_exception_on_missing_mesh_data", PropertiesParser::OptionalValue<bool>(desc.throw_exception_on_missing_mesh_data)}
					
				}
			);

			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
