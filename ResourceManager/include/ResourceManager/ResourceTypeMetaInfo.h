#pragma once

#include <ResourceManager/IResourceTypeMetaInfo.h>

namespace UnknownEngine
{
	namespace Resources
	{
		template<typename T>
		class ResourceTypeMetaInfo : public IResourceTypeMetaInfo
		{
		public:
			virtual ResourceType getType() = delete;
			static ResourceType staticGetType() = delete;
		};
	}
}
