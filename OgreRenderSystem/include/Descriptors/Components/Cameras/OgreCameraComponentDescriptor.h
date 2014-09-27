#pragma once

#include <ExportedMessages/LogMessage.h>
#include <Transform/Transform.h>
#include <AlignedNew.h>
#include <boost/optional.hpp>

namespace UnknownEngine
{
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreCameraComponentDescriptor
		{
			Core::LogMessage::Severity log_level;
			Core::Transform initial_transform;

			boost::optional<Math::Vector3> initial_look_at;
			boost::optional<Math::Scalar> near_clip_distance;
			boost::optional<Math::Scalar> far_clip_distance;

			std::string render_window_name;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreCameraComponentDescriptor() :
				log_level ( Core::LogMessage::Severity::LOG_SEVERITY_NONE ) {}
		};
	}
}
