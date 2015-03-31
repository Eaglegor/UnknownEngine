#pragma once

#include <atomic>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class RefCountingWrapper : public T
		{
		public:
			template<typename... Args>
			RefCountingWrapper(Args&& ...args):
			T(std::forward<Args>(args)...),
			ref_counter(1)
			{
			}

			void addRef()
			{
				ref_counter++;
			}
			
			void release()
			{
				if(--ref_counter == 0)
				{
					delete this;
				}
			}
		
			T& refCast()
			{
				return *this;
			}
		
		private:
			std::atomic_uint ref_counter;
			T* object;
		};
	}
}