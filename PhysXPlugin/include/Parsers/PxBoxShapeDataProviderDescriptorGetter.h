#pragma once

#include <boost/variant.hpp>
#include <Descriptors/DataProviders/PxBoxShapeDataProviderDesc.h>
#include <DataProviders/PxMaterialDataProvider.h>
#include <DescriptorContainer.h>
#include <Properties/Properties_fwd.h>
#include <Exception.h>
#include <CommonParsers/PropertiesParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PxBoxShapeDataProviderDescriptorGetter : public boost::static_visitor<PxBoxShapeDataProviderDesc>
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION ( NoDescriptorProvided );

				PxBoxShapeDataProviderDesc operator() ( const Core::DescriptorContainer& descriptor_container ) const
				{
					if ( descriptor_container.isEmpty() ) throw NoDescriptorProvided ( "Can't find descriptor for data provider" );
					return descriptor_container.get<PxBoxShapeDataProviderDesc>();
				}

				PxBoxShapeDataProviderDesc operator() ( const Core::Properties& properties ) const
				{
					PxBoxShapeDataProviderDesc desc;

					using Utils::PropertiesParser;

					PropertiesParser::parse
					(
					    properties,
					{
						{"width", PropertiesParser::RequiredValue<Math::Scalar> ( desc.width ) },
						{"height", PropertiesParser::RequiredValue<Math::Scalar> ( desc.height ) },
						{"depth", PropertiesParser::RequiredValue<Math::Scalar> ( desc.depth ) },
						{
							"PoseOffset",
							PropertiesParser::OptionalNestedValue
							(
							{
								{
									"position", PropertiesParser::OptionalValue<Math::Vector3> ( [&] ( const Math::Vector3 & vec )
									{
										desc.pose_offset.setPosition ( vec );
									} )
								},
								{
									"orientation_quat", PropertiesParser::OptionalValue<Math::Quaternion> ( [&] ( const Math::Quaternion & quat )
									{
										desc.pose_offset.setOrientation ( quat );
									} )
								}
							}
							)
						},
						{
							"material", PropertiesParser::RequiredRawValue<Loader::IDataProvider*> (
							    [&] ( Loader::IDataProvider * data_provider )
							{
								desc.material = dynamic_cast<PxMaterialDataProvider*> ( data_provider );
							}
							)
						},

					}
					);

					return desc;
				};
		};
	}
}
