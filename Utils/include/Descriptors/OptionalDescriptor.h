#pragma once

#include <Descriptors/Descriptor.h>
#include <type_traits>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename DescriptorType>
		class OptionalDescriptor : public IDescriptor
		{
			static_assert(std::is_base_of<Descriptor, DescriptorType>::value, "Only descriptor types (Utils::Descriptor) may be used with optional descriptor holder");

		public:
			virtual IDescriptor& operator= ( const Core::Properties& props )
			{
				desc = props;
				is_explicitly_initialized = true;
				return *this;
			}

			virtual operator Core::Properties(){
				return desc;
			};
			
			bool isExplicitlyInitialized()
			{
				return is_explicitly_initialized;
			}
			
			virtual bool isValid()
			{
				if(!is_explicitly_initialized) return true;
				return desc.isValid();
			}

			virtual DescriptorType* operator->()
			{
				return &desc;
			}
			
			virtual DescriptorType& get()
			{
				return desc;
			}
			
			virtual const DescriptorType& get() const
			{
				return desc;
			}
			
			
			
		private:
			bool is_explicitly_initialized = false; 
			DescriptorType desc;
			
		};
	}
}