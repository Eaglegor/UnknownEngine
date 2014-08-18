#pragma once 
#include <IComponentFactory.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreRenderSubsystem;
		class BaseOgreComponentFactory : public Core::IComponentFactory
		{
		public:
			virtual void destroyObject ( Core::Component* object );
			
			virtual ~BaseOgreComponentFactory();
			BaseOgreComponentFactory(OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper);
			
		protected:
			virtual void internalDestroyObject (Core::Component* object) = 0;
			
			std::unordered_set<Core::ComponentType> supported_types;
			Core::LogHelper* log_helper;
			OgreRenderSubsystem* render_subsystem;
			Core::EngineContext* engine_context;
		};
	}
}