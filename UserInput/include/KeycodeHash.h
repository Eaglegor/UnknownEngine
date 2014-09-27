#pragma once

#include <functional>
#include <Keys.h>

namespace std
{
	template<>
	struct hash<UnknownEngine::IO::Key>
	{
		size_t operator()(const UnknownEngine::IO::Key &key) const
		{
			return internal_hash_fn(static_cast<int>(key));
		};
		
	private:
		std::hash<int> internal_hash_fn;
	};
}