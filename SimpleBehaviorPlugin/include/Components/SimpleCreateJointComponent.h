#pragma once
#include <Components/SimpleBehaviorComponent.h>
#include <Descriptors/SimpleCreateJointComponentDesc.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Input/IContextualActionsMapper.h>
#include <ComponentInterfaces/RenderSystem/IRenderable.h>


namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
	}

	namespace Behavior
	{
		class SimpleCreateJointComponent : public Core::BaseComponent
		{
		public:
			SimpleCreateJointComponent ( const std::string& name, const SimpleCreateJointComponentDesc &desc);
			virtual ~SimpleCreateJointComponent();
			
			constexpr static const char* getTypeName(){return "Behavior.SimpleCreateJoint";}
			virtual Core::ComponentType getType() const override {return getTypeName();}
			virtual bool init () override;
			virtual void shutdown() override;
			
		private:
			void switchJoint();
			void createJoint();
			void destroyJoint();
			
			SimpleCreateJointComponentDesc desc;
			
			Core::IEntity* joint_entity;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::IContextualActionsMapper> input_context_mapper;
			Core::ComponentInterfacePtr<ComponentInterfaces::IRenderable> renderable_component;
		};
	}
}