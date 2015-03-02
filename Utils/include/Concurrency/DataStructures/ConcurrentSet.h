#pragma once
#include <Concurrency/DataStructures/LockingConcurrentSet.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		using ConcurrentSet = LockingConcurrentSet<T>;
	}
}