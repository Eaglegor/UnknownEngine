#pragma once

#include <SDLWindowManagerDescriptor.h>
#include <Properties/Properties_fwd.h>

namespace UnknownEngine
{

	namespace GUI
	{
		class SDLWindowManagerDescriptorParser
		{
		public:
			static SDLWindowManagerDescriptor parse(const Core::Properties& properties);
		};
	}
}