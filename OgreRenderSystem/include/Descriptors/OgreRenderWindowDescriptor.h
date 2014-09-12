#pragma once

namespace UnknownEngine
{
	namespace Graphics
	{
		struct OgreRenderWindowDescriptor
		{
			enum class WindowType
			{
				OWN,
				EXTERNAL,
				PARENT
			};
			
			std::string window_name;
			std::string window_title;
			size_t width;
			size_t height;
			WindowType type;
			bool fullscreen;
			
			OgreRenderWindowDescriptor():
			width(640),
			height(480),
			type(WindowType::OWN)
			{}
		};
	}
}