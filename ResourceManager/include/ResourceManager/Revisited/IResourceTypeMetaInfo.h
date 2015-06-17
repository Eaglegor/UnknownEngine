#pragma once

#include <ResourceManager/Revisited/ResourceType.h>

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

