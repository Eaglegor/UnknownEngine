#pragma once

#include <InlineSpecification.h>
#include <boost/any.hpp>

namespace UnknownEngine {
	namespace Core
	{
		class DescriptorContainer
		{
			public:
				DescriptorContainer(){}

				DescriptorContainer &operator=(const DescriptorContainer &rhs)
				{
					descriptor = rhs.descriptor;
					return *this;
				}

				DescriptorContainer(const DescriptorContainer& rhs)
					: descriptor(rhs.descriptor)
				{
				}

				DescriptorContainer(DescriptorContainer &&rhs)
					: descriptor(std::move(rhs.descriptor))
				{
				}

				template <typename DescriptorType>
				UNKNOWNENGINE_INLINE
				void set(const DescriptorType &desc)
				{
					this->descriptor = desc;
				}

				template <typename DescriptorType>
				UNKNOWNENGINE_INLINE
				const DescriptorType &get()
				{
					return boost::any_cast<DescriptorType>(descriptor);
				}

				UNKNOWNENGINE_INLINE
				const bool isEmpty()
				{
					return descriptor.empty();
				}

			private:
				boost::any descriptor;
		};
	}
}
