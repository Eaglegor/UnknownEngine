#pragma once

#include <ComponentSystem/BaseComponent.h>

namespace UnknownEngine
{
	namespace Core
	{
		class TransformHolderComponent : public BaseComponent
		{
			public:
				constexpr static const char* getTypeName()
				{
					return "Engine.TransformHolderComponent";
				}
			
				virtual Math::Vector3 getPosition() = 0;
				virtual Math::Quaternion getOrientation() = 0;
				virtual Math::Transform getTransform() = 0;
			
		};
	}
}