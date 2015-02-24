#pragma once

#include <boost/variant.hpp>
#include <Descriptors/SimpleEngineStopperDesc.h>
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
		class SimpleEngineStopperComponentDescriptorGetter : public boost::static_visitor<SimpleEngineStopperDesc>
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDescriptorProvided);

            SimpleEngineStopperDesc operator()(const Core::DescriptorContainer& descriptor) const
			{
				if(descriptor.isEmpty()) throw NoDescriptorProvided("No descriptor provided to create component");
				return descriptor.get<SimpleEngineStopperDesc>();
			}

            SimpleEngineStopperDesc operator()(const Core::Properties &properties) const
			{
                SimpleEngineStopperDesc desc;
				
				using Utils::PropertiesParser;

                desc.engine_starter_component = Core::ComponentsManager::getSingleton()->findComponent("Engine.Starter");

				Utils::PropertiesParser properties_parser;
				properties_parser.parse(
					properties,
					{
						{"input_context_name", PropertiesParser::RequiredValue<std::string>(desc.input_context_name)},
						{"input_context_mapping_provider_name", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value) {
							desc.input_context_mapping_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						}
						)}
					}
				);
				
				return desc;
			}
			
		};
	}
}