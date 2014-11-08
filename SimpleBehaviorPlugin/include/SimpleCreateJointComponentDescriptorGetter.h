#pragma once

#include <boost/variant.hpp>
#include <SimpleCreateJointComponentDesc.h>
#include <DescriptorContainer.h>
#include <Exception.h>
#include <Properties/Properties.h>
#include <CommonParsers/PropertiesParser.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class SimpleCreateJointComponentDescriptorGetter : public boost::static_visitor<SimpleCreateJointComponentDesc>
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDescriptorProvided);			
			
			SimpleCreateJointComponentDesc operator()(const Core::DescriptorContainer& descriptor) const
			{
				if(descriptor.isEmpty()) throw NoDescriptorProvided("No descriptor provided to create component");
				return descriptor.get<SimpleCreateJointComponentDesc>();
			}
			
			SimpleCreateJointComponentDesc operator()(const Core::Properties &properties) const
			{
				SimpleCreateJointComponentDesc desc;
				
				using Utils::PropertiesParser;
				
				Utils::PropertiesParser properties_parser;
				properties_parser.parse(
					properties,
					{
						{"input_context_name", PropertiesParser::RequiredValue<std::string>(desc.input_context_name)},
						{"create_joint_action_name", PropertiesParser::OptionalValue<std::string>(desc.create_joint_action_name)},
						{"body1_name", PropertiesParser::RequiredValue<std::string>(desc.body1_name)},
						{"body2_name", PropertiesParser::RequiredValue<std::string>(desc.body2_name)},
						{"jointed_material_name", PropertiesParser::RequiredValue<std::string>(desc.jointed_material_name)},
						{"free_material_name", PropertiesParser::RequiredValue<std::string>(desc.free_material_name)}
					}
				);
				
				return desc;
			}
			
		};
	}
}