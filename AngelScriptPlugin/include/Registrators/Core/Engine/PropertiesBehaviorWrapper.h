#pragma once

#include <DataProvider/IDataProvider.h>
#include <Properties/Properties.h>
#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		class PropertiesBehaviorWrapper
		{
		public:
			static const std::string& getString(Core::Properties* this_ptr, const std::string& name)
			{
				return this_ptr->get<std::string>(name);
			}
			
			static Loader::IDataProvider* getDataProvider(Core::Properties* this_ptr, const std::string& name)
			{
				return this_ptr->get<Loader::IDataProvider*>(name);
			}
			
			static Core::Properties& getNestedProperties(Core::Properties* this_ptr, const std::string& name)
			{
				return this_ptr->get_child(name);
			}
			
			static void setString(Core::Properties* this_ptr, const std::string& name, const std::string value)
			{
				this_ptr->set<std::string>(name, value);
			}
			
			static void setDataProvider(Core::Properties* this_ptr, const std::string& name, Loader::IDataProvider* value)
			{
				this_ptr->set<Loader::IDataProvider*>(name, value);
			}
			
			static void setNestedProperties(Core::Properties* this_ptr, const std::string& name, const Core::Properties& value)
			{
				this_ptr->set<Core::Properties>(name, value);
			}
		};
	}
}