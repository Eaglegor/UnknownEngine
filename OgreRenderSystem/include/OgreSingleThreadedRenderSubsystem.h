#pragma once

#include <OgreRenderSubsystem.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <Descriptors/OgreSingleThreadedRenderSubsystemDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreSingleThreadedRenderSubsystem : public OgreRenderSubsystem
		{
		public:
			OgreSingleThreadedRenderSubsystem(const char* name, const OgreSingleThreadedRenderSubsystemDescriptor& desc);
			
			constexpr static const char* getTypeName() {return "Ogre.SingleThreadRenderSubsystem";}
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual void init ( const Core::IEntity* parent_entity ) override;
			virtual void shutdown() override;
			
			virtual void onUpdateFrame ( Math::Scalar dt ) override;
			
		private:
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
		};
	}
}