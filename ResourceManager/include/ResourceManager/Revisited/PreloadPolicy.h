#pragma once

namespace UnknownEngine
{
	namespace Resources
	{
		enum class PreloadPolicy
		{
			AUTO, // Preload allowed - resource manager decides, when to start loading
			FORCE_PRELOAD, // Start loading immediately
			LAZY // Preload not allowed. Resource is loaded when it's referenced at the first time.
		};
	}
}
