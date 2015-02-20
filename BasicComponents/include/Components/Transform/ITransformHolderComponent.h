#pragma once

#include <ComponentSystem/IComponent.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ITransformHolderComponent
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