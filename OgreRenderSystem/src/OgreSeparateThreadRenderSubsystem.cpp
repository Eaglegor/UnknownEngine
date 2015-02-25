#include <OgreSeparateThreadRenderSubsystem.h>
#include <Descriptors/OgreSeparateThreadRenderSubsystemDescriptor.h>
#include <OgreRenderFrameListener.h>
#include <Components/BaseOgreComponent.h>
#include <OgreRoot.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreSeparateThreadRenderSubsystem::OgreSeparateThreadRenderSubsystem ( const char* name, const OgreSeparateThreadRenderSubsystemDescriptor& desc ):
		OgreRenderSubsystem ( name, desc.base_descriptor )
		{
		}

		OgreSeparateThreadRenderSubsystem::~OgreSeparateThreadRenderSubsystem()
		{
		}
		
		void OgreSeparateThreadRenderSubsystem::onUpdateFrame ( Math::Scalar dt )
		{
			{
				std::unique_lock<LockPrimitive> guard(initializing_components_lock);
				size_t count = initializing_components.size();
				for(int i = 0; i < count; ++i)
				{
					BaseOgreComponent* component = initializing_components.front();
					initializing_components.pop();
					if(component->getState() == BaseOgreComponent::State::INITIALIZATION)
					{
						guard.unlock();
						component->_init();
						guard.lock();
						components.emplace(component);
					}
					else
					{
						initializing_components.push(component);
					}
				}
			}
			
			UnknownEngine::Graphics::OgreRenderSubsystem::onUpdateFrame ( dt );
			
			{
				std::unique_lock<LockPrimitive> guard(shutting_down_components_lock);
				size_t count = shutting_down_components.size();
				for(int i = 0; i < count; ++i)
				{
					BaseOgreComponent* component = shutting_down_components.front();
					shutting_down_components.pop();
					if(component->getState() == BaseOgreComponent::State::SHUTTING_DOWN)
					{
						guard.unlock();
						component->_shutdown();
						guard.lock();
						components.erase(component);
					}
					else
					{
						shutting_down_components.push(component);
					}
				}
			}
			
			{
				std::unique_lock<LockPrimitive> guard(destructing_components_lock);
				size_t count = destructing_components.size();
				for(int i = 0; i < count; ++i)
				{
					BaseOgreComponent* component = destructing_components.front();
					destructing_components.pop();
					if(component->getState() == BaseOgreComponent::State::DELETION)
					{
						guard.unlock();
						component->_destroy();
						guard.lock();
					}
					else
					{
						destructing_components.push(component);
					}
				}
			}
		}
		
		void OgreSeparateThreadRenderSubsystem::init ()
		{
			listener.reset(new OgreRenderFrameListener(this));
			
			rendering_thread.reset(new std::thread( [this]()
			{
				this->OgreRenderSubsystem::init ();

				this->getRoot()->addFrameListener(listener.get());
				this->getRoot()->startRendering();
				this->getRoot()->removeFrameListener( listener.get() );
				
				this->OgreRenderSubsystem::shutdown();
				listener->setFinished();
			}
			));
		}

		void OgreSeparateThreadRenderSubsystem::shutdown()
		{
			listener->stopRendering();
			listener->waitUntilFinished();
			listener.reset();
		}
		
				
		void OgreSeparateThreadRenderSubsystem::initComponent ( BaseOgreComponent* component )
		{
			std::lock_guard<LockPrimitive> guard(initializing_components_lock);
			initializing_components.push(component);
		}

		void OgreSeparateThreadRenderSubsystem::shutdownComponent ( BaseOgreComponent* component )
		{
			std::lock_guard<LockPrimitive> guard(shutting_down_components_lock);
			shutting_down_components.push(component);
		}
		
		void OgreSeparateThreadRenderSubsystem::destroyComponent ( BaseOgreComponent* component )
		{
			std::lock_guard<LockPrimitive> guard(destructing_components_lock);
			destructing_components.push(component);
		}
		
	}
}