#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class MovableComponent;
		
		class TransformNotifierComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType()
				{
					return "TransformNotifierComponent";
				}

				virtual void addListener(MovableComponent* movable_component) = 0;
				virtual void removeListener(MovableComponent* movable_component) = 0;
		};
	}
}