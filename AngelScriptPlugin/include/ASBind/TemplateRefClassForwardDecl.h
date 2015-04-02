#pragma once

#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		class TemplateRefClassForwardDesc
		{
		public:
			TemplateRefClassForwardDecl(const std::string &name, Behavior::AngelScriptSubsystem *subsystem)
			{
				if(!subsystem->typeInfoIsBound<T>())
				{
					subsystem->bindTypeInfo<T>(name, ClassType::REF_TYPE);
					subsystem->getScriptEngine()->RegisterObjectType(name.c_str(), 0, asOBJ_REF | asOBJ_TEMPLATE);
				}
			}
		};
	}
}