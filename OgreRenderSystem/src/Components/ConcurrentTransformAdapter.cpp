#include <Components/ConcurrentTransformAdapter.h>
#include <mutex>

namespace UnknownEngine
{
	namespace Graphics
	{
		ConcurrentTransformAdapter::ConcurrentTransformAdapter():
		transform_changed(false)
		{
		}
		
		void ConcurrentTransformAdapter::apply ( ComponentInterfaces::MovableComponent* component )
		{
			std::lock_guard<LockPrimitive> guard(transform_lock);
			if(transform_changed)
			{
				component->setTransform(new_transform);
				transform_changed = false;
			}
		}
		
		void ConcurrentTransformAdapter::setOrientation ( const Math::Quaternion& quaternion )
		{
			std::lock_guard<LockPrimitive> guard(transform_lock);
			new_transform.setOrientation(quaternion);
			transform_changed = true;
		}

		void ConcurrentTransformAdapter::setPosition ( const Math::Vector3& position )
		{
			std::lock_guard<LockPrimitive> guard(transform_lock);
			new_transform.setPosition(position);
			transform_changed = true;
		}

		void ConcurrentTransformAdapter::setTransform ( const Math::Transform& transform )
		{
			std::lock_guard<LockPrimitive> guard(transform_lock);
			new_transform = transform;
			transform_changed = true;
		}
	}
}