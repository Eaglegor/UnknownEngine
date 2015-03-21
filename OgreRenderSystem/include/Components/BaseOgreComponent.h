#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <functional>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreRenderSubsystem;
		
		class BaseOgreComponent : public Core::BaseComponent
		{
			public:
				enum class State
				{
					CREATION,
					INITIALIZATION,
					WORK,
					SHUTTING_DOWN,
					DELETION
				};
				
				BaseOgreComponent ( const std::string &name, OgreRenderSubsystem* render_subsystem );
				virtual ~BaseOgreComponent();

				virtual bool init () override final;
				virtual void shutdown() override final;

				void _init ();
				virtual void _update(){};
				void _shutdown();
				void _destroy();
				
				void setDestructionCallback(std::function<void(Core::IComponent*)> callback);
				
				State getState() const;
				
			protected:
				OgreRenderSubsystem* getRenderSubsystem(){return render_subsystem;}
				
			private:
				virtual void internalInit () = 0;
				virtual void internalShutdown( ) = 0;
				
				OgreRenderSubsystem* render_subsystem;
				
				std::function<void(Core::IComponent*)> destruction_callback;
				
				volatile State state;
		};

	}
}
