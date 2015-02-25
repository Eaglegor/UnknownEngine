#include <stdafx.h>

#include <MainLoop/MainLoopComponent.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageSender.h>
#include <Profiling/AverageFpsCounter.h>
#include <Profiling/SimpleFpsPrinter.h>
#include <Profiling/TimeCounter.h>
#include <Scalar.h>
#include <ResourceManager/ResourceManager.h>


namespace UnknownEngine
{
	namespace Core
	{

		MainLoopComponent::MainLoopComponent (const char* name) :
			Core::BaseComponent(name),
			stopped ( true )
		{
		}

		MainLoopComponent::~MainLoopComponent ()
		{
			// TODO Auto-generated destructor stub
		}

		void MainLoopComponent::start ()
		{
			stopped = false;

			Utils::TimeCounter time_counter;
			time_counter.tick();
			
			while ( !stopped )
			{
				time_counter.tick();

				for(ComponentInterfaces::UpdateFrameListenerComponent* listener : listeners)
				{
					listener->onUpdateFrame(time_counter.getDt());
				}
			}
		}

		void MainLoopComponent::stop()
		{
			stopped = true;
		}
		
		void MainLoopComponent::addListener ( ComponentInterfaces::UpdateFrameListenerComponent* listener )
		{
			listeners.insert(listener);
		}

		void MainLoopComponent::removeListener ( ComponentInterfaces::UpdateFrameListenerComponent* listener )
		{
			listeners.erase(listener);
		}

		ComponentType MainLoopComponent::getType() const
		{
			return Core::ComponentType(getTypeName());
		}

		void MainLoopComponent::init ()
		{

		}

		void MainLoopComponent::shutdown()
		{

		}
		
		IComponentInterface* MainLoopComponent::getInterface ( const ComponentType& type )
		{
			if(type == ComponentInterfaces::FrameUpdaterComponent::getTypeName()) return this;
			return nullptr;
		}

		
	} /* namespace Core */
} /* namespace UnknownEngine */
