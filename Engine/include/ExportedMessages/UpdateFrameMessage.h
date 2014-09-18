#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Frame synchronization message
		 *
		 * This message is broadcasted every frame by MainLoop.
		 * It may be sent more than once per frame.
		 *
		 */
		struct UpdateFrameMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.MainLoop.UpdateFrameMessage";}
			
			/**
			 * @brief Updating stage
			 *
			 * To separate some actions from another you can tell engine to send this message on
			 * different update stages. For instance, you can update physics and logic on preprocessing stage
			 * and rendering - on processing stage.
			 *
			 */
			enum Stage
			{
			    PREPROCESSING = 0, PROCESSING = 1, POSTPROCESSING = 2
			};

			Stage stage; ///< Update stage
			float dt; ///< Delta time from last frame
		};

		
	} /* namespace Core */
} /* namespace UnknownEngine */
