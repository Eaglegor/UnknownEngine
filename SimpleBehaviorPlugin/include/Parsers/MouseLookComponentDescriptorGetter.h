#pragma once

#include <boost/variant.hpp>
#include <Descriptors/MouseLookComponentDesc.h>
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
		class MouseLookComponentDescriptorGetter : public boost::static_visitor<MouseLookComponentDesc>
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDescriptorProvided);			
			
			MouseLookComponentDesc operator()(const Core::DescriptorContainer& descriptor) const
			{
				if(descriptor.isEmpty()) throw NoDescriptorProvided("No descriptor provided to create component");
				return descriptor.get<MouseLookComponentDesc>();
			}
			
			MouseLookComponentDesc operator()(const Core::Properties &properties) const
			{
				MouseLookComponentDesc desc;
				
				using Utils::PropertiesParser;
				
				Utils::PropertiesParser properties_parser;
				properties_parser.parse(
					properties,
					{
						{"input_context_name", PropertiesParser::RequiredValue<std::string>(desc.input_context_name)},
						{"InitialTransform",
							PropertiesParser::OptionalNestedValue(
								{
									{"position", PropertiesParser::OptionalValue<Math::Vector3>([&](const Math::Vector3 &vec){desc.initial_transform.setPosition(vec);})},
									{"orientation", PropertiesParser::OptionalValue<Math::Quaternion>([&](const Math::Quaternion &quat){desc.initial_transform.setOrientation(quat);})}
								}
							)
						},
						{"move_forward_action_name", PropertiesParser::OptionalValue<std::string>(desc.move_forward_action_name)},
						{"move_backward_action_name", PropertiesParser::OptionalValue<std::string>(desc.move_backward_action_name)},
						{"strafe_left_action_name", PropertiesParser::OptionalValue<std::string>(desc.strafe_left_action_name)},
						{"strafe_right_action_name", PropertiesParser::OptionalValue<std::string>(desc.strafe_right_action_name)},
						{"strafe_up_action_name", PropertiesParser::OptionalValue<std::string>(desc.strafe_up_action_name)},
						{"strafe_down_action_name", PropertiesParser::OptionalValue<std::string>(desc.strafe_down_action_name)},
						{"yaw_action_name", PropertiesParser::OptionalValue<std::string>(desc.yaw_action_name)},
						{"pitch_action_name", PropertiesParser::OptionalValue<std::string>(desc.pitch_action_name)},
						{"linear_speed", PropertiesParser::OptionalValue<Math::Scalar>(desc.linear_speed)},
						{"angular_speed", PropertiesParser::OptionalValue<Math::Scalar>(desc.angular_speed)},
						{"update_frame_provider_name", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value) {
							desc.update_frame_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						}
						)},
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