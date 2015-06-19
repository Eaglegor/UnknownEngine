#pragma once

#include <ResourceManager/ResourceType.h>

namespace UnknownEngine
{
	namespace Resources
	{
		class IResourceTypeMetaInfo
		{
		public:
			virtual ~IResourceTypeMetaInfo(){}
			virtual ResourceType getType() = 0;
		};
	}
}

