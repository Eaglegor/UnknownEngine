#pragma once

namespace UnknownEngine
{
	namespace Resources
	{
		class IResourceHandle
		{
		public:
			virtual ~IResourceHandle(){}

			virtual void reserve() = 0;
			virtual void release() = 0;
			virtual void lock() = 0;
			virtual void unlock() = 0;
			virtual ResourceType getType() = 0;
			virtual void* getData() = 0;
			virtual size_t getDataSize() = 0;
		};
	}
}
