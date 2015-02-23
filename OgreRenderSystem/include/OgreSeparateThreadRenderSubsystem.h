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
			
			virtual void init ( const Core::IEntity* parent_entity );
			virtual void shutdown();
			
		private:
			std::unique_ptr<std::thread> rendering_thread;
			std::unique_ptr<OgreRenderFrameListener> listener;
		};
	}
}