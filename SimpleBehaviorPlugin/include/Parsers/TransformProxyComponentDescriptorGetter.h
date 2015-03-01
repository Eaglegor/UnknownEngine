#pragma once

#include <boost/variant.hpp>
#include <Descriptors/TransformProxyComponentDesc.h>
#include <DescriptorContainer.h>
#include <Exception.h>
#include <Properties/Properties.h>
#include <CommonParsers/PropertiesParser.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class TransformProxyComponentDescriptorGetter : public boost::static_visitor<TransformProxyComponentDesc>
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDescriptorProvided);

            TransformProxyComponentDesc operator()(const Core::DescriptorContainer& descriptor) const
			{
				if(descriptor.isEmpty()) throw NoDescriptorProvided("No descriptor provided to create component");
				return descriptor.get<TransformProxyComponentDesc>();
			}

            TransformProxyComponentDesc operator()(const Core::Properties &properties) const
			{
                TransformProxyComponentDesc desc;
				
				using Utils::PropertiesParser;

				Utils::PropertiesParser properties_parser;
				properties_parser.parse(
					properties,
					{
						{"transform_provider", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value) {
							desc.transform_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						}
						)},
						{"transform_receiver", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value) {
							desc.transform_receiver = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						}
						)}
					}
				);
				
				return desc;
			}
			
		};
	}
}