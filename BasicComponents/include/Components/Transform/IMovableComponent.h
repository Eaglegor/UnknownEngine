#pragma once

#include <ComponentSystem/BaseComponent.h>

namespace UnknownEngine
{
	namespace Core
	{
		class MovableComponent : public BaseComponent
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