#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/RenderSystem/Common/VisibilityChecker.h>
#include <ComponentInterfaces/RenderSystem/Common/VisibilityData.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class VerboseVisibilityChecker : public VisibilityChecker
		{
			public:
				constexpr static const char* getType(){return "VerboseVisibilityChecker";}
				
				virtual VisibilityData getVisibilityData() const = 0;
		};
	}
}