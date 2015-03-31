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
				RefClassForwardDecl(const std::string &name, Behavior::AngelScriptSubsystem *subsystem):
				name(name)
				{
					if(!subsystem->typeNameIsBound<T>())
					{
						subsystem->bindTypeName<T>(name);
						subsystem->getScriptEngine()->RegisterObjectType(name.c_str(), 0, asOBJ_REF);
					}
				}
		};
	}
}
