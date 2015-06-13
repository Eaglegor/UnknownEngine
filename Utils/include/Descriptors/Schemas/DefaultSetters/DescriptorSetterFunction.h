#pragma once

#include <functional>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename C, typename T>
		using RawDescriptorSetterFunction = std::function<void (C&, const T&)>;
		
		template<typename T>
		using DescriptorSetterFunction = std::function<void (const T&)>;
	}
}