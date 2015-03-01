#pragma once

#include <boost/variant.hpp>
#include <Descriptors/SimpleStopperDesc.h>
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
		class SimpleStopperComponentDescriptorGetter : public boost::static_visitor<SimpleStopperDesc>
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDescriptorProvided);

            SimpleStopperDesc operator()(const Core::DescriptorContainer& descriptor) const
			{
				if(descriptor.isEmpty()) throw NoDescriptorProvided("No descriptor provided to create component");
				return descriptor.get<SimpleStopperDesc>();
			}

            SimpleStopperDesc operator()(const Core::Properties &properties) const
			{
                SimpleStopperDesc desc;
				
				using Utils::PropertiesParser;

				Utils::PropertiesParser properties_parser;
				properties_parser.parse(
					properties,
					{
						{"input_context_name", PropertiesParser::RequiredValue<std::string>(desc.input_context_name)},
						{"action_name", PropertiesParser::RequiredValue<std::string>(desc.action_name)},
						{"input_context_mapping_provider_name", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value) {
							desc.input_context_mapping_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						}
						)},
						{"stoppable_component_name", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value) {
							desc.stoppable_component = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						}
						)}
					}
				);
				
				return desc;
			}
			
		};
	}
}