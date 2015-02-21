#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class MovableComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getTypeName()
				{
					return "Interface.MovableComponent";
				}
			
				virtual Math::Vector3 setPosition() = 0;
				virtual Math::Quaternion setOrientation() = 0;
				virtual Math::Transform setTransform() = 0;
			
		};
	}
}