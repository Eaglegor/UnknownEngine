#include <stdafx.h>

#include <Components/BaseOgreComponent.h>
#include <OgreRenderSubsystem.h>
#include <Logging.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine {
	namespace Graphics
	{
		BaseOgreComponent::BaseOgreComponent ( const std::string& name, OgreRenderSubsystem* render_subsystem ) :
			Core::BaseComponent(name.c_str()),
			render_subsystem ( render_subsystem ),
			state(State::CREATION)
		{
			Core::ComponentsManager::getSingleton()->reserveComponent(render_subsystem);
		}
		
		BaseOgreComponent::~BaseOgreComponent() {
			Core::ComponentsManager::getSingleton()->releaseComponent(render_subsystem);
		}

		bool BaseOgreComponent::init ()
		{
			if(state == State::CREATION)
			{
				state = State::INITIALIZATION;
				render_subsystem->initComponent(this);
			}
			return true;
		}
		
		void BaseOgreComponent::shutdown()
		{
			if(state == State::WORK)
			{
				state = State::SHUTTING_DOWN;
				render_subsystem->shutdownComponent(this);
			}
		}

		void BaseOgreComponent::_init()
		{
			internalInit();
			state = State::WORK;
		}

		void BaseOgreComponent::_shutdown()
		{
			if(state == State::WORK)
			{
				internalShutdown();
			}
			state = State::DELETION;
		}

		void BaseOgreComponent::_destroy()
		{
			if(destruction_callback) 
			{
				destruction_callback(this);
			}
		}

		void BaseOgreComponent::setDestructionCallback ( std::function< void (Core::IComponent*)> callback )
		{
			destruction_callback = callback;
			render_subsystem->destroyComponent(this);
		}
		
		BaseOgreComponent::State BaseOgreComponent::getState() const
		{
			return state;
		}

	}
}