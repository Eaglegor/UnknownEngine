#pragma once

#include <Descriptors/Schemas/IDescriptorSettersFactory.h>
#include <Descriptors/Schemas/DescriptorFieldSetter.h>
#include <functional>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename C, typename T>
		class DescriptorSettersFactory : public IDescriptorSettersFactory<C>
		{
		public:
			DescriptorSettersFactory(RawDescriptorSetterFunction<C, T> setter_function):
			setter_function(setter_function)
			{}
			
			virtual IDescriptorFieldSetter* createSetter ( C& parent)
			{
				DescriptorSetterFunction<T> func = std::bind(setter_function, parent, std::placeholders::_1);
				return new DescriptorFieldSetter<T>(func);
			}

			virtual void destroySetter ( IDescriptorFieldSetter *setter )
			{
				delete setter;
			}
			
		private:
			RawDescriptorSetterFunction<C, T> setter_function;
		};
	}
}