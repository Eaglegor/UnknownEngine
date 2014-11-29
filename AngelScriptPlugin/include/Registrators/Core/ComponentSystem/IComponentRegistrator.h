#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <Objects/IComponent.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class IComponentRegistrator : public ClassReferenceTypeRegistrator<Core::IComponent>
		{
			public:
				IComponentRegistrator() :
					ClassReferenceTypeRegistrator< Core::IComponent > ( "IComponent", CORE_AS_NAMESPACE_NAME )
				{}
		};
	}
}
