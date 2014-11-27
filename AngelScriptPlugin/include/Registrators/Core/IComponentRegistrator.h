#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <Objects/IComponent.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class IComponentRegistrator : public ClassReferenceTypeRegistrator<Core::IComponent>
		{
			public:
				IComponentRegistrator(const std::string& registered_name, const std::string& declaration_namespace = "") :
					ClassReferenceTypeRegistrator< Core::IComponent > ( registered_name, declaration_namespace )
				{}
		};
	}
}
