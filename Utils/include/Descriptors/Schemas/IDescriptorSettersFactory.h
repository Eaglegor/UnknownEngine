#pragma once

#include <Descriptors/Schemas/IDescriptorFieldSetter.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename C>
		class IDescriptorSettersFactory
		{
		public:
			virtual ~IDescriptorSettersFactory(){}
			
			virtual IDescriptorFieldSetter* createSetter(C& parent) = 0;
			virtual void destroySetter(IDescriptorFieldSetter* setter) = 0;
		};
	}
}