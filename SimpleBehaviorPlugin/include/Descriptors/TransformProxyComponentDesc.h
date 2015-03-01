#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Behavior
	{
		struct TransformProxyComponentDesc
		{
			Core::IComponent* transform_provider;
			Core::IComponent* transform_receiver;
			
			TransformProxyComponentDesc():
			transform_provider(nullptr),
			transform_receiver(nullptr)
			{}
		};
	}
}