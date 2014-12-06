#pragma once

#include <Descriptors/Components/Lights/OgreLightSettings.h>
#include <AlignedNew.h>
#include <ExportedMessages/LogMessage.h>
#include <Transform/Transform.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgrePointLightComponentDescriptor
		{
			OgreLightSettings light_settings;

			Math::Transform initial_transform;
			Core::LogSeverity log_level;

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgrePointLightComponentDescriptor() :
				log_level ( Core::LogSeverity::NONE )
			{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgrePointLightComponentDescriptor);