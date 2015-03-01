#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct GetOgreRenderTargetMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Graphics.OgreRenderSystem.GetOgreRenderTargetMessage";}
			
			std::string render_target_name;
			std::function<void(Ogre::RenderTarget*)> value_return_callback;
		};
	}
}