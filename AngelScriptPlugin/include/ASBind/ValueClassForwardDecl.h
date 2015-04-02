#pragma once

#include <angelscript.h>
#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{

		template<typename T>
		class ValueClassForwardDecl
		{
			public:
				ValueClassForwardDecl(const std::string &name, Behavior::AngelScriptSubsystem *subsystem)
				{
					if(!subsystem->typeInfoIsBound<T>())
					{
						subsystem->bindTypeInfo<T>(name, ClassType::VALUE_TYPE);
						subsystem->getScriptEngine()->RegisterObjectType(name.c_str(), sizeof(T), asOBJ_VALUE | asGetTypeTraits<T>());
					}
				}
		};
	}
}
