#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ICEGuiContext.h>
#include <ICEGuiComponent.h>

namespace UnknownEngine
{
	namespace GUI
	{
		class BaseCEGuiComponent : public Core::BaseComponent, public ICEGuiComponent
		{
		public:
			BaseCEGuiComponent(const char* name, ICEGuiContext* context):
			Core::BaseComponent(name),
			state(CREATION),
			context(context)
			{}


			State getState() const override {return state;}

			virtual bool init () final
			{
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
			}

			virtual void _update() = 0;

			virtual void _destroy() final
			{
				destruction_callback(this);
			}

			virtual void startDestruction(DestructionCallback destruction_callback)
			{
				this->destruction_callback = destruction_callback;
				state = State::DESTRUCTION;
				context->destroyComponent(this);
			}

		private:
			virtual void internalInit() = 0;
			virtual void internalShutdown() = 0;

			State state;
			ICEGuiContext* context;

			DestructionCallback destruction_callback;
		};

	}
}