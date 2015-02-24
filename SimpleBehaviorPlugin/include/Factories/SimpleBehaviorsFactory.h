#pragma once

#include <InlineSpecification.h>
#include <ComponentSystem/BaseComponentFactory.h>
#include <memory>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseComponentListener;
		class EngineContext;
	}

	namespace Behavior
	{

		class SimpleBehaviorsPerformer;

		class SimpleBehaviorsFactory : public Core::BaseComponentFactory
		{
		public:
			SimpleBehaviorsFactory( UnknownEngine::Core::EngineContext* engine_context);
			virtual const char* getName() const override;

		private:
			Core::IComponent* createSimpleRotationComponent(const Core::ComponentDesc& desc);
			Core::IComponent* createMouseLookComponent(const Core::ComponentDesc& desc);
			Core::IComponent* createSimpleCreateJointComponent(const Core::ComponentDesc& desc);
            Core::IComponent* createSimpleStopperComponent(const Core::ComponentDesc& desc);
			
			Core::EngineContext* engine_context;
		};
		
	}
}