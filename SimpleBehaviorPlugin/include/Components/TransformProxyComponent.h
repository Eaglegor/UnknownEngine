#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/Transform/MovableComponent.h>
#include <ComponentInterfaces/Transform/TransformNotifierComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <Descriptors/TransformProxyComponentDesc.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class TransformProxyComponent : 
		public Core::BaseComponent,
		public ComponentInterfaces::MovableComponent
		{
		public:
			TransformProxyComponent(const char* name, const TransformProxyComponentDesc &desc);
			~TransformProxyComponent();
			
			constexpr static const char* getTypeName(){return "Behavior.TransformProxyComponent";}
			virtual Core::ComponentType getType() const override {return getTypeName();}
			
			virtual bool init() override;
			virtual void shutdown() override;
			
			virtual void setOrientation ( const Math::Quaternion& quaternion ) override;
			virtual void setPosition ( const Math::Vector3& position ) override;
			virtual void setTransform ( const Math::Transform& transform ) override;
			
		private:
			Core::ComponentInterfacePtr<ComponentInterfaces::TransformNotifierComponent> transform_provider;
			Core::ComponentInterfacePtr<ComponentInterfaces::MovableComponent> transform_receiver;
		};
	}
}