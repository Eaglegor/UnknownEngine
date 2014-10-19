#pragma once

#include <boost/variant.hpp>
#include <Descriptors/DataProviders/PxMaterialDataProviderDesc.h>
#include <DescriptorContainer.h>
#include <Properties/Properties_fwd.h>
#include <Exception.h>
#include <CommonParsers/PropertiesParser.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PxMaterialDataProviderDescriptorGetter : public boost::static_visitor<PxMaterialDataProviderDesc>
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION ( NoDescriptorProvided );

				PxMaterialDataProviderDesc operator() ( const Core::DescriptorContainer& descriptor_container ) const
				{
					if ( descriptor_container.isEmpty() ) throw NoDescriptorProvided ( "Can't find descriptor for data provider" );
					return descriptor_container.get<PxMaterialDataProviderDesc>();
				}

				PxMaterialDataProviderDesc operator() ( const Core::Properties& properties ) const
				{
					PxMaterialDataProviderDesc desc;

					using Utils::PropertiesParser;

					PropertiesParser::parse
					(
					    properties,
					{
						{"static_friction", PropertiesParser::RequiredValue<Math::Scalar> ( desc.static_friction ) },
						{"dynamic_friction", PropertiesParser::RequiredValue<Math::Scalar> ( desc.dynamic_friction ) },
						{"restitution", PropertiesParser::RequiredValue<Math::Scalar> ( desc.restitution ) }
						//{"log_level", PropertiesParser::OptionalValue<Core::LogMessage::Severity> ( desc.log_level ) },
					}
					);

					return desc;
				};
		};
	}
}
