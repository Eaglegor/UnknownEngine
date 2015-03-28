#pragma once

#include <AlignedNew.h>
#include <Descriptors/Components/Lights/OgreLightSettings.h>
#include <Transform/Transform.h>
#include <LogSeverity.h>
#include <Descriptors/CommonDescriptors/TransformDescriptor.h>
#include <Descriptors/DescriptorUtils.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreSpotLightComponentDescriptor : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			OgreLightSettings light_settings;

			Utils::OptionalDescriptor<Utils::TransformDescriptor> initial_transform;
			Utils::OptionalProperty<Core::LogSeverity> log_level;

			Utils::OptionalProperty<Math::Vector3> initial_look_at;
			Utils::OptionalProperty<Math::Vector3> initial_direction;

			Utils::OptionalProperty<Math::Scalar> inner_angle;
			Utils::OptionalProperty<Math::Scalar> outer_angle;
			Utils::OptionalProperty<Math::Scalar> falloff;

			Utils::OptionalComponentDependency transform_provider;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreSpotLightComponentDescriptor() :
				log_level ( Core::LogSeverity::NONE )
			{
				UEDESC_ADD_NESTED_DESCRIPTOR(light_settings);
				UEDESC_ADD_NESTED_DESCRIPTOR(initial_transform);
				UEDESC_ADD_FIELD(log_level);
				UEDESC_ADD_FIELD(initial_look_at);
				UEDESC_ADD_FIELD(initial_direction);
				UEDESC_ADD_FIELD(inner_angle);
				UEDESC_ADD_FIELD(outer_angle);
				UEDESC_ADD_FIELD(falloff);
				UEDESC_ADD_FIELD(transform_provider);
			}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreSpotLightComponentDescriptor);