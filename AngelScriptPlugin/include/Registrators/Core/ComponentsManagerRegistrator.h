#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <ComponentDesc.h>
#include <ComponentsManager.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ComponentsManagerRegistrator : public ClassReferenceTypeRegistrator<Core::ComponentsManager>
		{
		protected:
			virtual bool registerMembers ( asIScriptEngine* script_engine ) const override
			{
				return true;
			}
		};
	}
}