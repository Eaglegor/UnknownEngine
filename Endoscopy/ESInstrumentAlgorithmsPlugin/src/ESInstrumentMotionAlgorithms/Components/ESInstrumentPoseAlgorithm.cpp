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
		transform_changed_message_sender(name)
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
			const Math::Scalar X_LOWER_LIMIT = -1;
			const Math::Scalar X_HIGHER_LIMIT = 1;
			const Math::Scalar Y_LOWER_LIMIT = -1;
			const Math::Scalar Y_HIGHER_LIMIT = 1;
			const Math::Scalar Z_LOWER_LIMIT = -1;
			const Math::Scalar Z_HIGHER_LIMIT = 1;
			const Math::Scalar D_LOWER_LIMIT = 0;
			const Math::Scalar D_HIGHER_LIMIT = 20;

			const Math::Vector3 INSTRUMENT_PORT_POSITION(0, 0, 0);
			const Math::Vector3 INSTRUMENT_DIRECTION = -Math::Z_AXIS;

			Utils::ValueRangeMapper<Math::Scalar> x_range_mapper(0, 1, X_LOWER_LIMIT, X_HIGHER_LIMIT);
			Utils::ValueRangeMapper<Math::Scalar> y_range_mapper(0, 1, Y_LOWER_LIMIT, Y_HIGHER_LIMIT);
			Utils::ValueRangeMapper<Math::Scalar> z_range_mapper(0, 1, Z_LOWER_LIMIT, Z_HIGHER_LIMIT);
			Utils::ValueRangeMapper<Math::Scalar> d_range_mapper(0, 1, D_LOWER_LIMIT, D_HIGHER_LIMIT);

			Math::Scalar x = x_range_mapper.getMappedValue(msg.new_x_axis);
			Math::Scalar y = y_range_mapper.getMappedValue(msg.new_y_axis);
			Math::Scalar z = z_range_mapper.getMappedValue(msg.new_z_axis);
			Math::Scalar d = d_range_mapper.getMappedValue(msg.new_d_axis);

			Math::Quaternion x_quat(Math::AngleAxis(x, Math::X_AXIS));
			Math::Quaternion y_quat(Math::AngleAxis(y, Math::Y_AXIS));
			Math::Quaternion z_quat(Math::AngleAxis(z, Math::Z_AXIS));

			Core::TransformChangedMessage transform_msg;
			transform_msg.new_transform.setOrientation(x_quat * y_quat * z_quat);
			transform_msg.new_transform.setPosition(INSTRUMENT_PORT_POSITION + transform_msg.new_transform.getOrientation() * INSTRUMENT_DIRECTION * d);

			transform_changed_message_sender.sendMessage(transform_msg);
		}
		
	}
}