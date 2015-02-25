#include <ESInstrumentMotionAlgorithms/Components/ESInstrumentPoseAlgorithm.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ExportedMessages/EndoscopicHardware/ESHardwareOrientationChangedMessage.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ValueRangeMapper.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{

		static int RANGE_VALUE = 1;
		
		ESInstrumentPoseAlgorithm::ESInstrumentPoseAlgorithm ( const char* name, const ESInstrumentPoseAlgorithmDesc& desc ):
		BaseComponent ( name ),
		desc(desc),
		transform_changed_message_sender(name),
		x_range_mapper(-1, 1, -RANGE_VALUE, RANGE_VALUE),
		y_range_mapper(-1, 1, -RANGE_VALUE, RANGE_VALUE),
		z_range_mapper(-1, 1, -RANGE_VALUE, RANGE_VALUE),
		d_range_mapper(-1, 1, -RANGE_VALUE, RANGE_VALUE*10)
		{
			this->desc.lower_x = -RANGE_VALUE;
			this->desc.higher_x = RANGE_VALUE;
			this->desc.lower_y = -RANGE_VALUE;
			this->desc.higher_y = RANGE_VALUE;
			this->desc.lower_z = -RANGE_VALUE;
			this->desc.higher_z = RANGE_VALUE;
			this->desc.lower_d = -RANGE_VALUE;
			this->desc.higher_d = RANGE_VALUE*10;
			this->desc.instrument_direction = -Math::Z_AXIS;
			this->desc.instrument_port_position = Math::Vector3(0, 0, 0);
		}

		Core::ComponentType ESInstrumentPoseAlgorithm::getType() const
		{
			return Core::ComponentType(getTypeName());
		}

		bool ESInstrumentPoseAlgorithm::init ()
		{
			return true;
		}

		void ESInstrumentPoseAlgorithm::shutdown()
		{
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