#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ICEGuiComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiContextComponent.h>

namespace UnknownEngine
{
	namespace GUI
	{
		class BaseCEGuiComponent : public Core::BaseComponent, public ICEGuiComponent
		{
		public:
			BaseCEGuiComponent(const char* name, Core::IComponent* context):
			Core::BaseComponent(name),
			state(State::CREATION),
			context(context)
			{}

			State getState() const override {return state;}

			virtual bool init () final
			{
				if(!context) return false;
				state = State::INITIALIZATION;
				context->initComponent(this);
				return true;
			}

			virtual void shutdown () final
			{
				state = State::SHUTTING_DOWN;
				context->shutdownComponent(this);
			}

			virtual void _init() final
			{
				internalInit();
				state = State::WORK;
			}

			virtual void _shutdown() final
			{
				internalShutdown();
				state = State::DESTRUCTION;
			}

			virtual void _update() = 0;

			virtual void _destroy() final
			{
				destruction_callback(this);
			}

			virtual void startDestruction(DestructionCallback destruction_callback)
			{
				this->destruction_callback = destruction_callback;
				if(context) 
				{
					context->destroyComponent(this);
				}
				else 
				{
					_destroy();
				}
			}

		private:
			virtual void internalInit() = 0;
			virtual void internalShutdown() = 0;

			State state;

			DestructionCallback destruction_callback;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::CEGuiContextComponent> context;
		};

	}
}