#pragma once

#include <ResourceManager/Revisited/ResourceType.h>

namespace UnknownEngine
{
	namespace Resources
	{
		class IResourceHandle
		{
		public:
			virtual ~IResourceHandle(){}

			virtual const char* getName() = 0;
			virtual const char* getResourceGroupName() = 0;

			virtual void reserve() = 0;
			virtual void release() = 0;
			virtual ResourceType getResourceType() = 0;
			virtual void* getData() = 0;
		};
	}
}
