#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/RenderSystem/Common/IRenderable.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class VisibilityCheckerListener : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "VisibilityChecker";}
				
				virtual void onObjectVisible(IRenderable* renderable) = 0;
				virtual void onObjectInvisible(IRenderable* renderable) = 0;
		};
	}
}