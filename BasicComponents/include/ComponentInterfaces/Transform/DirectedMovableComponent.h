#pragma once

#include <ComponentInterfaces/Transform/MovableComponent.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class DirectedMovableComponent : public MovableComponent
		{
			public:
				constexpr static const char* getTypeName()
				{
					return "DirectedMovableComponent";
				}
		
				virtual void setDirection(const Math::Vector3 &direction);
				virtual void lookAt(const Math::Vector3 &look_at_position);
				
		};
	}
}