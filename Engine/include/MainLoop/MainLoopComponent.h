#pragma once

#include <Engine_export.h>
#include <vector>
#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentSystem/BaseComponent.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;

		class MainLoopComponent :
                public BaseComponent,
                public ComponentInterfaces::FrameUpdaterComponent
		{
			public:
				ENGINE_EXPORT
				MainLoopComponent (const char* name);

				ENGINE_EXPORT
				virtual ~MainLoopComponent ();

				constexpr static const char* getTypeName(){return "Engine.MainLoopComponent";}
				
				ENGINE_EXPORT
				virtual ComponentType getType() const;
				
				ENGINE_EXPORT
				virtual bool init ();
				
				ENGINE_EXPORT
				virtual void shutdown();
				
				ENGINE_EXPORT
				void start();
				
				ENGINE_EXPORT
				void stop();
				
				ENGINE_EXPORT
				virtual IComponentInterface* getInterface ( const ComponentType& type );
				
				virtual void addListener ( ComponentInterfaces::UpdateFrameListenerComponent* listener );
				virtual void removeListener ( ComponentInterfaces::UpdateFrameListenerComponent* listener );
				
			private:
				volatile bool stopped;

				std::unordered_set<ComponentInterfaces::UpdateFrameListenerComponent*> listeners;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
