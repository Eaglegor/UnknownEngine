#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <EngineContext.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class EngineContextRegistrator : public ClassReferenceTypeRegistrator<Core::EngineContext>
		{
			public:
				EngineContextRegistrator() :
					ClassReferenceTypeRegistrator< Core::EngineContext > ( "EngineContext", CORE_AS_NAMESPACE_NAME )
				{}
		};
	}
}
