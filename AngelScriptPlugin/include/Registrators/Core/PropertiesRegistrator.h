#pragma once

#include <Properties/Properties.h>
#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class PropertiesRegistrator : public ClassValueTypeRegistrator<Core::Properties>
		{
			public:
				PropertiesRegistrator() :
					ClassValueTypeRegistrator< Core::Properties > ( "Properties", CORE_AS_NAMESPACE_NAME )
				{}

			protected:
				virtual bool registerMethods ( asIScriptEngine* script_engine ) const override
				{
					return true;
				}
		};
	}
}
