#pragma once

#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
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
			
			std::string window_title;
			size_t width;
			size_t height;
			WindowType type;
			bool fullscreen;
			
			Core::IComponent* parent_window;
			
			Core::LogSeverity log_level;
			
			OgreRenderWindowDescriptor():
			width(640),
			height(480),
			type(WindowType::OWN),
			parent_window(nullptr)
			{}
		};
	}
}