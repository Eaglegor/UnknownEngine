#pragma once

#include <angelscript.h>
#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{

		template<typename T>
		class RefClassForwardDecl
		{
			public:
				RefClassForwardDecl(const std::string &name, Behavior::AngelScriptSubsystem *subsystem)
				{
					if(!subsystem->typeInfoIsBound<T>())
					{
						subsystem->bindTypeInfo<T>(name, ClassType::REF_TYPE);
						subsystem->getScriptEngine()->RegisterObjectType(name.c_str(), 0, asOBJ_REF);
					}
				}
		};
	}
}
