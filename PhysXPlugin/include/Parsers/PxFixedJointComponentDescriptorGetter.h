#pragma once

#include <boost/variant.hpp>
#include <Descriptors/Components/PxFixedJointComponentDesc.h>
#include <DescriptorContainer.h>
#include <Properties/Properties_fwd.h>
#include <Exception.h>
#include <CommonParsers/PropertiesParser.h>
#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PxFixedJointComponentDescriptorGetter : public boost::static_visitor<PxFixedJointComponentDesc>
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION ( NoDescriptorProvided );

				PxFixedJointComponentDesc operator() (const Core::DescriptorContainer& descriptor_container) const
				{
					if ( descriptor_container.isEmpty() ) throw NoDescriptorProvided ( "Can't find descriptor for component" );
					return descriptor_container.get<PxFixedJointComponentDesc>();
				}

				PxFixedJointComponentDesc operator() (const Core::Properties& properties) const
				{
					PxFixedJointComponentDesc desc;

					using Utils::PropertiesParser;

					PropertiesParser::parse
					(
					    properties,
					{
						{"actor1_name", PropertiesParser::RequiredValue<std::string>( [&desc](const std::string& value){
							desc.actor1 = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						})},
						{"actor2_name", PropertiesParser::RequiredValue<std::string>( [&desc](const std::string& value){
							desc.actor2 = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						})},
						{"use_projection", PropertiesParser::OptionalValue<bool>(desc.use_projection) },
						{"collision_enabled", PropertiesParser::OptionalValue<bool>(desc.collision_enabled) },
						{"projection_linear_tolerance", PropertiesParser::OptionalValue<Math::Scalar> ( desc.projection_linear_tolerance ) },
						{ "projection_angular_tolerance", PropertiesParser::OptionalValue<Math::Scalar>(desc.projection_angular_tolerance) }
					}
					);

					return desc;
				};
		};
	}
}
