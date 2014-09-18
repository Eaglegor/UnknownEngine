#pragma once

#include <Vectors/Vector3.h>
#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		/**
		 * @brief Command for camera to look at some position
		 *
		 */
		struct CameraLookAtActionMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Graphics.CameraLookAtActionMessage";}
			
			Math::Vector3 look_at_position;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
