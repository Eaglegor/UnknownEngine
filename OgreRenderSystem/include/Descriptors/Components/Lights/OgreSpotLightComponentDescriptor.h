#pragma once

#include <AlignedNew.h>
#include <Descriptors/Components/Lights/OgreLightSettings.h>
#include <Transform/Transform.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreSpotLightComponentDescriptor
		{
			OgreLightSettings light_settings;

			Math::Transform initial_transform;
			Core::LogSeverity log_level;

			boost::optional<Math::Vector3> initial_look_at;
			boost::optional<Math::Vector3> initial_direction;

			boost::optional<Math::Scalar> inner_angle;
			boost::optional<Math::Scalar> outer_angle;
			boost::optional<Math::Scalar> falloff;

			Core::IComponent* transform_provider;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreSpotLightComponentDescriptor() :
				log_level ( Core::LogSeverity::NONE ),
				transform_provider(nullptr)
			{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreSpotLightComponentDescriptor);