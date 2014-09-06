#pragma once

#include <Descriptors/OgreRenderWindowDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		class OgreRenderWindowDescriptorParser
		{
		public:
			static OgreRenderWindowDescriptor parse( const Core::Properties& properties );
			
		};
		
	}
}