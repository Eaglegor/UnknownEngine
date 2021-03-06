#pragma once

#include <boost/variant.hpp>
#include <Descriptors/SimpleRotationComponentDesc.h>
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
		class SimpleRotationComponentDescriptorGetter : public boost::static_visitor<SimpleRotationComponentDesc>
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDescriptorProvided);			
			
			SimpleRotationComponentDesc operator()(const Core::DescriptorContainer& descriptor) const
			{
				if(descriptor.isEmpty()) return SimpleRotationComponentDesc();
				return descriptor.get<SimpleRotationComponentDesc>();
			}
			
			SimpleRotationComponentDesc operator()(const Core::Properties &properties) const
			{
				SimpleRotationComponentDesc desc;
				
				using Utils::PropertiesParser;
				
				Utils::PropertiesParser properties_parser;
				properties_parser.parse(
					properties,
					{
						{"InitialTransform",
							PropertiesParser::OptionalNestedValue(
								{
									{"position", PropertiesParser::OptionalValue<Math::Vector3>([&](const Math::Vector3 &vec){desc.initial_transform.setPosition(vec);})},
									{"orientation", PropertiesParser::OptionalValue<Math::Quaternion>([&](const Math::Quaternion &quat){desc.initial_transform.setOrientation(quat);})}
								}
							)
						},
						{"update_frame_provider_name", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value){
							desc.update_frame_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						})}
					}
				);
				
				return desc;
			}
			
		};
	}
}