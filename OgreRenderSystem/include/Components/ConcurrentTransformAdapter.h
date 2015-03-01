#pragma once

#include <Spinlock.h>
#include <Transform/Transform.h>
#include <ComponentInterfaces/Transform/MovableComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class ConcurrentTransformAdapter : public ComponentInterfaces::MovableComponent
		{
		public:
			ConcurrentTransformAdapter();
			void apply(ComponentInterfaces::MovableComponent* component);
			
			void setTransform(const Math::Transform& new_transform) override;
			void setPosition(const Math::Vector3& new_transform) override;
			void setOrientation(const Math::Quaternion& new_transform) override;
			
		private:
			typedef Utils::Spinlock LockPrimitive;
			LockPrimitive transform_lock;
			volatile bool transform_changed;
			Math::Transform new_transform;
		};
	}
}