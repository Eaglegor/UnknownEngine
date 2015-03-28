#pragma once

#include <Transform/Transform.h>
#include <AlignedNew.h>
#include <boost/optional.hpp>
#include <LogSeverity.h>
#include <Descriptors/DescriptorUtils.h>
#include <Descriptors/CommonDescriptors/TransformDescriptor.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreCameraComponentDescriptor : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			Utils::OptionalProperty<Core::LogSeverity> log_level;
			Utils::OptionalDescriptor<Utils::TransformDescriptor> initial_transform;
			
			Utils::OptionalProperty<Math::Vector3> initial_look_at;
			Utils::OptionalProperty<Math::Scalar> near_clip_distance;
			Utils::OptionalProperty<Math::Scalar> far_clip_distance;

			Utils::RequiredComponentDependency render_window;
			Utils::OptionalComponentDependency transform_provider;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreCameraComponentDescriptor() :
			log_level ( Core::LogSeverity::NONE )
			{
				UEDESC_ADD_FIELD(log_level);
				UEDESC_ADD_NESTED_DESCRIPTOR(initial_transform);
				UEDESC_ADD_FIELD(initial_look_at);
				UEDESC_ADD_FIELD(near_clip_distance);
				UEDESC_ADD_FIELD(far_clip_distance);
				UEDESC_ADD_FIELD(render_window);
				UEDESC_ADD_FIELD(transform_provider);
			}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreCameraComponentDescriptor);