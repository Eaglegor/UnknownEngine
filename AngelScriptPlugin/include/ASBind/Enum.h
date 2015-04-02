#pragma once

#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		class Enum
		{
		public:
			Enum(const std::string &name, Behavior::AngelScriptSubsystem* subsystem):
			name(name),
			subsystem(subsystem)
			{
				subsystem->getScriptEngine()->RegisterEnum(name.c_str());
			}
			
			Enum& value(const std::string& value_name, int value)
			{
				subsystem->getScriptEngine()->RegisterEnumValue(name.c_str(), value_name.c_str(), value);
				return *this;
			}
			
		private:
			std::string name;
			Behavior::AngelScriptSubsystem* subsystem;
		};
	}
}