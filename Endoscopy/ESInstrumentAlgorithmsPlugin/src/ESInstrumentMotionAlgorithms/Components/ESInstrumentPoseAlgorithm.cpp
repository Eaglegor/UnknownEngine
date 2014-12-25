#include <ESInstrumentMotionAlgorithms/Components/ESInstrumentPoseAlgorithm.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ExportedMessages/EndoscopicHardware/ESHardwareOrientationChangedMessage.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ValueRangeMapper.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		
		ESInstrumentPoseAlgorithm::ESInstrumentPoseAlgorithm ( const char* name, const ESInstrumentPoseAlgorithmDesc& desc ):
		BaseComponent ( name ),
		desc(desc),
		transform_changed_message_sender(name),
		x_range_mapper(0, 1, desc.lower_x, desc.higher_x),
		y_range_mapper(0, 1, desc.lower_y, desc.higher_y),
		z_range_mapper(0, 1, desc.lower_z, desc.higher_z),
		d_range_mapper(0, 1, desc.lower_d, desc.higher_d)
		{
			this->desc.lower_x = -1;
			this->desc.higher_x = 1;
			this->desc.lower_y = -1;
			this->desc.higher_y = 1;
			this->desc.lower_z = -1;
			this->desc.higher_z = 1;
			this->desc.lower_d = 0;
			this->desc.higher_d = 20;
			this->desc.instrument_direction = -Math::Z_AXIS;
			this->desc.instrument_port_position = Math::Vector3(0, 0, 0);
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
			Math::Scalar x = x_range_mapper.getMappedValue(msg.new_x_axis);
			Math::Scalar y = y_range_mapper.getMappedValue(msg.new_y_axis);
			Math::Scalar z = z_range_mapper.getMappedValue(msg.new_z_axis);
			Math::Scalar d = d_range_mapper.getMappedValue(msg.new_d_axis);

			Math::Quaternion x_quat(Math::AngleAxis(x, Math::X_AXIS));
			Math::Quaternion y_quat(Math::AngleAxis(y, Math::Y_AXIS));
			Math::Quaternion z_quat(Math::AngleAxis(z, Math::Z_AXIS));

			Core::TransformChangedMessage transform_msg;
			transform_msg.new_transform.setOrientation(x_quat * y_quat * z_quat);
			transform_msg.new_transform.setPosition(desc.instrument_port_position + transform_msg.new_transform.getOrientation() * desc.instrument_direction * d);

			transform_changed_message_sender.sendMessage(transform_msg);
		}
		
	}
}