#pragma once

namespace UnknownEngine
{
	namespace IO
	{
		
		enum class MouseAxis
		{
			X,
			Y,
			Z
		};
		
	}
}

namespace std
{
	template<>
	struct hash<UnknownEngine::IO::MouseAxis>
	{
	public:
		size_t operator()(const UnknownEngine::IO::MouseAxis &axis) const
		{
			return hash_fn(static_cast<int>(axis));
		};
		
	private:
		hash<int> hash_fn;
	};
}