#pragma once

#include <functional>
#include <ResourceManager/Revisited/ResourceHandle.h>

namespace UnknownEngine
{
	namespace Resources
	{
		class ObsoleteResourceHandleListener
		{
			public:
				virtual ~ObsoleteResourceHandleListener(){}

				ObsoleteResourceHandleListener(std::function<void (ResourceHandle*)> callback):
				callback(callback)
				{
				}

				void onHandleObsolete(ResourceHandle* handle)
				{
					if(callback) callback(handle);
				}

			private:
				std::function<void (ResourceHandle*)> callback;
		};
	}
}
