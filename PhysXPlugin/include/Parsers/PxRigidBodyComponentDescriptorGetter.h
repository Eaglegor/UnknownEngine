#pragma once

#include <boost/variant.hpp>
#include <Descriptors/Components/PxRigidBodyComponentDesc.h>
#include <DataProvider/IDataProvider.h>
#include <DataProviders/PxShapeDataProvider.h>
#include <DescriptorContainer.h>
#include <Properties/Properties_fwd.h>
#include <Exception.h>
#include <CommonParsers/PropertiesParser.h>

#include <Parsers/RigidBodyDynamicsTypeLexicalCast.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/QuaternionParser.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PxRigidBodyComponentDescriptorGetter : public boost::static_visitor<PxRigidBodyComponentDesc>
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION ( NoDescriptorProvided );

				PxRigidBodyComponentDesc operator() (const Core::DescriptorContainer& descriptor_container) const
				{
					if ( descriptor_container.isEmpty() ) throw NoDescriptorProvided ( "Can't find descriptor for component" );
					return descriptor_container.get<PxRigidBodyComponentDesc>();
				}

				PxRigidBodyComponentDesc operator() (const Core::Properties& properties) const
				{
					PxRigidBodyComponentDesc desc;

					using Utils::PropertiesParser;

					PropertiesParser::parse
					(
					    properties,
					{
						{
							"shape", PropertiesParser::RequiredRawValue<Loader::IDataProvider*>(
							[&](Loader::IDataProvider * data_provider)
							{
								desc.shape_data_provider = dynamic_cast<PxShapeDataProvider*> (data_provider);
							}
							)
						},
						{
							"LocalShapeTransform",
							PropertiesParser::OptionalNestedValue
							(
							{
								{
									"position", PropertiesParser::OptionalValue<Math::Vector3>([&](const Math::Vector3 & vec)
									{
										desc.local_shape_transform.setPosition(vec);
									})
								},
								{
									"orientation_quat", PropertiesParser::OptionalValue<Math::Quaternion>([&](const Math::Quaternion & quat)
									{
										desc.local_shape_transform.setOrientation(quat);
									})
								}
							}
							)
						},
						{
							"InitialTransform",
							PropertiesParser::OptionalNestedValue
							(
							{
								{
									"position", PropertiesParser::OptionalValue<Math::Vector3>([&](const Math::Vector3 & vec)
									{
										desc.initial_transform.setPosition(vec);
									})
								},
								{
									"orientation_quat", PropertiesParser::OptionalValue<Math::Quaternion>([&](const Math::Quaternion & quat)
									{
										desc.initial_transform.setOrientation(quat);
									})
								}
							}
							)
						},
						{"mass", PropertiesParser::RequiredValue<Math::Scalar>( desc.mass )},
						{"dynamics_type", PropertiesParser::RequiredValue<RigidBodyDynamicsType> ( desc.dynamics_type ) },
						{"linear_damping", PropertiesParser::OptionalValue<Math::Scalar> ( desc.linear_damping ) },
						{ "angular_damping", PropertiesParser::OptionalValue<Math::Scalar>( desc.angular_damping ) },
						{ "max_angular_velocity", PropertiesParser::OptionalValue<Math::Scalar>(desc.max_angular_velocity ) },
						{ "stabilization_threshold", PropertiesParser::OptionalValue<Math::Scalar>(desc.stabilization_threshold) },
						{ "position_iterations", PropertiesParser::OptionalValue<size_t>(desc.position_iterations) },
						{ "velocity_iterations", PropertiesParser::OptionalValue<size_t>(desc.velocity_iterations) },
						{ "contact_report_threshold", PropertiesParser::OptionalValue<Math::Scalar>(desc.contact_report_threshold) }
					}
					);

					return desc;
				};
		};
	}
}
