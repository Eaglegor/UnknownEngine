#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/OgreHOQVisibilityCheckerDesc.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreHOQVisibilityCheckerDescriptorParser
		{
			public:
				static OgreHOQVisibilityCheckerDesc parse ( const Core::Properties& properties );
		};
	}
}