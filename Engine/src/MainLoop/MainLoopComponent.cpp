#include <stdafx.h>

#include <MainLoop/MainLoopComponent.h>
#include <Profiling/AverageFpsCounter.h>
#include <Profiling/SimpleFpsPrinter.h>
#include <Profiling/TimeCounter.h>
#include <Scalar.h>
#include <ResourceManager/ResourceManager.h>


namespace UnknownEngine
{
	namespace Core
	{

		MainLoopComponent::MainLoopComponent ( const char* name ) :
			Core::BaseComponent ( name ),
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

				update_frame_observer.doForAllListeners (
				    [&time_counter] ( ComponentInterfaces::UpdateFrameListenerComponent * listener )
					{
						listener->onUpdateFrame ( time_counter.getDt() );
					}
				);
			}
		}

		void MainLoopComponent::stop()
		{
			stopped = true;
		}

		void MainLoopComponent::addListener ( ComponentInterfaces::UpdateFrameListenerComponent* listener )
		{
			update_frame_observer.addListener ( listener );
		}

		void MainLoopComponent::removeListener ( ComponentInterfaces::UpdateFrameListenerComponent* listener )
		{
			update_frame_observer.addListener ( listener );
		}

		ComponentType MainLoopComponent::getType() const
		{
			return Core::ComponentType ( getTypeName() );
		}

		bool MainLoopComponent::init ()
		{
			return true;
		}

		void MainLoopComponent::shutdown()
		{

		}

		IComponentInterface* MainLoopComponent::getInterface ( const ComponentType& type )
		{
			if ( type == ComponentInterfaces::FrameUpdaterComponent::getType() ) return this;
			return nullptr;
		}


	} /* namespace Core */
} /* namespace UnknownEngine */
