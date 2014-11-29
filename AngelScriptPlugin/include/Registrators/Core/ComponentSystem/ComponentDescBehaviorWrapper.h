#pragma once

#include <ComponentDesc.h>
#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ComponentDescBehaviorWrapper
		{
		public:
			static Core::Properties& get_descriptor(Core::ComponentDesc* this_ptr)
			{
				return boost::get<Core::Properties>(this_ptr->descriptor);
			}
			
			static void set_descriptor(Core::ComponentDesc* this_ptr, Core::Properties &value)
			{
				this_ptr->descriptor = value;
			}
			
		};
	}
}