#pragma once

#include <Descriptors/Components/Lights/OgreLightSettings.h>
#include <Transform/Transform.h>
#include <ExportedMessages/LogMessage.h>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreDirectionalLightComponentDescriptor
		{
			OgreLightSettings light_settings;

			Math::Transform initial_transform;
			Core::LogSeverity log_level;

			boost::optional<Math::Vector3> initial_look_at;
			boost::optional<Math::Vector3> initial_direction;

			Core::IComponent* transform_provider;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreDirectionalLightComponentDescriptor() :
				log_level ( Core::LogSeverity::NONE ),
				transform_provider(nullptr)
			{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreDirectionalLightComponentDescriptor);