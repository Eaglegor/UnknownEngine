#pragma once

namespace UnknownEngine
{
	namespace Endoscopy
	{
		enum class ESInstrumentPort
		{
			LEFT,
			RIGHT,
			CAMERA
		};
	}
}

namespace std
{
	template<>
	struct hash<UnknownEngine::Endoscopy::ESInstrumentPort>
	{
		int operator()(const UnknownEngine::Endoscopy::ESInstrumentPort &port) const
		{
			return std::hash<int>()(static_cast<int>(port));
		}
	};
}