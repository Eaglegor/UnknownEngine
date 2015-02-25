#pragma once

#include <OgreRenderSubsystem.h>
#include <thread>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreRenderFrameListener;

		struct OgreSeparateThreadRenderSubsystemDescriptor;
		class OgreSeparateThreadRenderSubsystem : public OgreRenderSubsystem
		{
		public:
			OgreSeparateThreadRenderSubsystem ( const char* name, const OgreSeparateThreadRenderSubsystemDescriptor& desc );
			virtual ~OgreSeparateThreadRenderSubsystem();
			
			constexpr static const char* getTypeName() {return "Ogre.SeparateThreadRenderSubsystem";}
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual void onUpdateFrame ( Math::Scalar dt ) override;
			
			virtual bool init () override;
			virtual void shutdown() override;

			virtual void initComponent ( BaseOgreComponent* component ) override;
			virtual void shutdownComponent ( BaseOgreComponent* component ) override;
			virtual void destroyComponent ( BaseOgreComponent* component ) override;
			
		private:
			std::unique_ptr<std::thread> rendering_thread;
			std::unique_ptr<OgreRenderFrameListener> listener;
			
			std::queue<BaseOgreComponent*> initializing_components;
			std::queue<BaseOgreComponent*> shutting_down_components;
			std::queue<BaseOgreComponent*> destructing_components;
			
			typedef std::mutex LockPrimitive;
			LockPrimitive initializing_components_lock;
			LockPrimitive shutting_down_components_lock;
			LockPrimitive destructing_components_lock;
		};
	}
}