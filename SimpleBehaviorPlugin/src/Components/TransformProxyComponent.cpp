#include <Components/TransformProxyComponent.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		TransformProxyComponent::TransformProxyComponent(const char* name, const TransformProxyComponentDesc &desc):
		BaseComponent(name),
		transform_provider(desc.transform_provider),
		transform_receiver(desc.transform_receiver)
		{
		}

		TransformProxyComponent::~TransformProxyComponent()
		{

		}

		bool TransformProxyComponent::init()
		{
			if(!transform_provider || !transform_receiver) return false;
			transform_provider->addListener(this);
			return true;
		}

		void TransformProxyComponent::shutdown()
		{
			transform_provider->removeListener(this);
		}

		void TransformProxyComponent::setOrientation ( const Math::Quaternion& quaternion )
		{
			transform_receiver->setOrientation(quaternion);
		}

		void TransformProxyComponent::setPosition ( const Math::Vector3& position )
		{
			transform_receiver->setPosition(position);
		}

		void TransformProxyComponent::setTransform ( const Math::Transform& transform )
		{
			transform_receiver->setTransform(transform);
		}
	}
}