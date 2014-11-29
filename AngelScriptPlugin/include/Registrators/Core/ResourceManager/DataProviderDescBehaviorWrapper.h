#pragma once

#include <DataProvider/DataProviderDesc.h>
#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		class DataProviderDescBehaviorWrapper
		{
		public:
			static Core::Properties& get_descriptor(Loader::DataProviderDesc* this_ptr)
			{
				return boost::get<Core::Properties>(this_ptr->descriptor);
			}
			
			static void set_descriptor(Loader::DataProviderDesc* this_ptr, Core::Properties &value)
			{
				return this_ptr->descriptor = value;
			}
			
		};
	}
}