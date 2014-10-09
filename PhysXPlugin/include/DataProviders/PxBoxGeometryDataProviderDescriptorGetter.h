#pragma once
#include <Descriptors/DataProviders/PxBoxGeometryDataProviderDesc.h>
#include <CommonParsers/PropertiesParser.h>
#include <DescriptorContainer.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Physics
	{
		class PxBoxGeometryDataProviderDescriptorGetter : public boost::static_visitor<PxBoxGeometryDataProviderDesc>
		{
		public:
			
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDescriptorProvided);
			
			PxBoxGeometryDataProviderDesc operator()(const Core::DescriptorContainer& descriptor_container)
			{
				if(descriptor_container.isEmpty()) throw NoDescriptorProvided("Can't find descriptor for data provider");
				return descriptor_container.get<PxBoxGeometryDataProviderDesc>();
			}
			
			PxBoxGeometryDataProviderDesc operator()(const Core::Properties &creation_options)
			{
				PxBoxGeometryDataProviderDesc desc;
				
				using Utils::PropertiesParser;
			
				PropertiesParser::parse
				(
					creation_options,
					{
						{"width", PropertiesParser::RequiredValue<Math::Scalar>(desc.width)},
						{"height", PropertiesParser::RequiredValue<Math::Scalar>(desc.height)},
						{"depth", PropertiesParser::RequiredValue<Math::Scalar>(desc.depth)}
					}
				);
				
				return desc;
			}
		};
	}
}