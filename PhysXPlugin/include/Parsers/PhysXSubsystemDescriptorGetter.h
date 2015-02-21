#pragma once

#include <boost/variant.hpp>
#include <DescriptorContainer.h>
#include <Properties/Properties_fwd.h>
#include <Exception.h>
#include <CommonParsers/PropertiesParser.h>

#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <CommonParsers/Vector3Parser.h>
#include <Descriptors/PhysXSubsystemDesc.h>
#include <Logging.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PhysXSubsystemDescriptorGetter : public boost::static_visitor<PhysXSubsystemDesc>
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION ( NoDescriptorProvided );

				PhysXSubsystemDesc operator() (const Core::DescriptorContainer& descriptor_container) const
				{
					if ( descriptor_container.isEmpty() ) throw NoDescriptorProvided ( "Can't find descriptor for component" );
					return descriptor_container.get<PhysXSubsystemDesc>();
				}

				PhysXSubsystemDesc operator() (const Core::Properties& properties) const
				{
					PhysXSubsystemDesc desc;

					using Utils::PropertiesParser;

					PropertiesParser::parse
					(
					    properties,
					{
						{"enable_hardware", PropertiesParser::OptionalValue<bool> ( desc.enable_hardware ) },
						{"cpu_threads_count", PropertiesParser::OptionalValue<size_t> ( desc.cpu_threads_count ) },
						{"length_tolerance_scale", PropertiesParser::OptionalValue<Math::Scalar> ( desc.length_tolerance_scale ) },
						{"mass_tolerance_scale", PropertiesParser::OptionalValue<Math::Scalar> ( desc.mass_tolerance_scale ) },
						{"speed_tolerance_scale", PropertiesParser::OptionalValue<Math::Scalar> ( desc.speed_tolerance_scale ) },
						{"track_outstanding_allocations", PropertiesParser::OptionalValue<bool> ( desc.track_outstanding_allocations ) },
						{"enable_profiling", PropertiesParser::OptionalValue<bool> ( desc.enable_profiling ) },
						{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity> ( desc.log_level ) },
						{"gravity", PropertiesParser::RequiredValue<Math::Vector3> ( desc.gravity ) },
						{"update_frame_provider_name", PropertiesParser::RequiredValue<std::string>([&desc](const std::string& value) {
							desc.update_frame_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
						}
						)}
					}
					);

					return desc;
				};
		};
	}
}
