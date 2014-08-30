#pragma once

#include <InlineSpecification.h>
#include <BaseComponentFactory.h>
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
			SimpleBehaviorsFactory( UnknownEngine::Core::EngineContext* engine_context, SimpleBehaviorsPerformer* behaviors_performer );
			virtual const char* getName();	

		private:
			Core::IComponent* createSimpleRotationComponent(const Core::ComponentDesc& desc);
			
			void destroySimpleBehaviorComponent(Core::IComponent* object);
			
			SimpleBehaviorsPerformer* behaviors_performer;
			Core::EngineContext* engine_context;
		};
		
	}
}