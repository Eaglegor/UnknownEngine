#pragma once

#include <ExportedMessages/LogMessage.h>
#include <Transform/Transform.h>
#include <AlignedNew.h>
#include <boost/optional.hpp>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreCameraComponentDescriptor
		{
			Core::LogSeverity log_level;
			Math::Transform initial_transform;

			boost::optional<Math::Vector3> initial_look_at;
			boost::optional<Math::Scalar> near_clip_distance;
			boost::optional<Math::Scalar> far_clip_distance;

			Core::IComponent* render_window;
			Core::IComponent* transform_provider;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreCameraComponentDescriptor() :
				log_level ( Core::LogSeverity::NONE ),
				render_window(nullptr),
				transform_provider(nullptr)
				{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreCameraComponentDescriptor);