#pragma once

#include <ComponentSystem/IComponent.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IMovableComponent
		{
			public:
				constexpr static const char* getTypeName()
				{
					return "Engine.MovableComponent";
				}
			
				virtual Math::Vector3 setPosition() = 0;
				virtual Math::Quaternion setOrientation() = 0;
				virtual Math::Transform setTransform() = 0;
			
		}
	}
}