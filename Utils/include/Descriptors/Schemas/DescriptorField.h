#pragma once

#include <Descriptors/Schemas/IDescriptorSettersFactory.h>
#include <memory>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename C>
		struct DescriptorField
		{
			std::shared_ptr<IDescriptorSettersFactory<C>> setters_factory;
			bool is_optional = false;
		};
	}
}