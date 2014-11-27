#pragma once

#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <EngineContext.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class EngineContextRegistrator : public ClassReferenceTypeRegistrator<Core::EngineContext>
		{
			public:
				EngineContextRegistrator(const std::string& registered_name, const std::string& declaration_namespace = "") :
					ClassReferenceTypeRegistrator< Core::EngineContext > ( registered_name, declaration_namespace )
				{}
		};
	}
}
