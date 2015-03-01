#pragma once

#include <Descriptors/Components/Lights/OgreLightSettings.h>
#include <AlignedNew.h>
#include <Transform/Transform.h>
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgrePointLightComponentDescriptor
		{
			OgreLightSettings light_settings;

			Math::Transform initial_transform;
			Core::LogSeverity log_level;

			Core::IComponent* transform_provider;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgrePointLightComponentDescriptor() :
				log_level ( Core::LogSeverity::NONE ),
				transform_provider(nullptr)
			{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgrePointLightComponentDescriptor);