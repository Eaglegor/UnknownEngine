#include <ESInstrumentMotionAlgorithms/Components/ESInstrumentPoseAlgorithm.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ExportedMessages/EndoscopicHardware/ESHardwareOrientationChangedMessage.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		
		ESInstrumentPoseAlgorithm::ESInstrumentPoseAlgorithm ( const char* name, const ESInstrumentPoseAlgorithmDesc& desc ):
		BaseComponent ( name ),
		desc(desc)
		{
		}

		Core::ComponentType ESInstrumentPoseAlgorithm::getType() const
		{
			return Core::ComponentType(getTypeName());
		}

		void ESInstrumentPoseAlgorithm::init ( const Core::IEntity* parent_entity )
		{
			listener.reset(new Core::BaseMessageListener(getName()));
			
			{
				typedef ESHardwareOrientationChangedMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
				
				listener->createMessageBuffer<MessageType, BufferType>(this, &ESInstrumentPoseAlgorithm::onHardwarePoseUpdate);
			}
			
			listener->registerAtDispatcher();
		}

		void ESInstrumentPoseAlgorithm::shutdown()
		{
			listener->unregisterAtDispatcher();
			
			listener.reset();
		}

		void ESInstrumentPoseAlgorithm::onHardwarePoseUpdate ( const ESHardwareOrientationChangedMessage& msg )
		{
			
		}
		
	}
}