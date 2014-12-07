#pragma once

#include <Vectors/Vector3.h>
#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) CameraLookAtActionMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Graphics.CameraLookAtActionMessage";}
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			Math::Vector3 look_at_position;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::CameraLookAtActionMessage);