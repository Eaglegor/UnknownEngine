#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <Transform/Transform.h>
#include <Vectors/Vector3.h>
#include <Quaternion.h>

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
			
				virtual void setPosition(const Math::Vector3 &position) = 0;
				virtual void setOrientation(const Math::Quaternion &quaternion) = 0;
				virtual void setTransform(const Math::Transform &transform) = 0;
			
		};
	}
}