#pragma once

#include <AlignedNew.h>
#include <Descriptors/Components/Lights/OgreLightSettings.h>
#include <Transform/Transform.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreSpotLightComponentDescriptor
		{
			OgreLightSettings light_settings;

			Core::Transform initial_transform;
			Core::LogMessage::Severity log_level;

			boost::optional<Math::Vector3> initial_look_at;
			boost::optional<Math::Vector3> initial_direction;

			boost::optional<Math::Scalar> inner_angle;
			boost::optional<Math::Scalar> outer_angle;
			boost::optional<Math::Scalar> falloff;

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreSpotLightComponentDescriptor() :
				log_level ( Core::LogMessage::Severity::LOG_SEVERITY_NONE )
			{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreSpotLightComponentDescriptor);