#pragma once

#include <Descriptors/Components/Lights/OgreLightSettings.h>
#include <Transform/Transform.h>
#include <ExportedMessages/LogMessage.h>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreDirectionalLightComponentDescriptor
		{
			OgreLightSettings light_settings;

			Core::Transform initial_transform;
			Core::LogMessage::Severity log_level;

			boost::optional<Math::Vector3> initial_look_at;
			boost::optional<Math::Vector3> initial_direction;

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreDirectionalLightComponentDescriptor() :
				log_level ( Core::LogMessage::Severity::LOG_SEVERITY_NONE )
			{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreDirectionalLightComponentDescriptor);