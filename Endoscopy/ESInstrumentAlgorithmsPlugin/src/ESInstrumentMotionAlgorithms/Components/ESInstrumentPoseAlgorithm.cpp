#include <ESInstrumentMotionAlgorithms/Components/ESInstrumentPoseAlgorithm.h>
#include <MessageSystem/BaseMessageListener.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ValueRangeMapper.h>
#include <Transform/Transform.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{

		static int RANGE_VALUE = 1;
		
		ESInstrumentPoseAlgorithm::ESInstrumentPoseAlgorithm ( const char* name, const ESInstrumentPoseAlgorithmDesc& desc ):
		BaseComponent ( name ),
		desc(desc),
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
		}

		void ESInstrumentPoseAlgorithm::onHardwareStateUpdate ( Math::Scalar x, Math::Scalar y, Math::Scalar z, Math::Scalar d )
		{
			Math::Scalar mx = x_range_mapper.getMappedValue(x);
			Math::Scalar my = y_range_mapper.getMappedValue(y);
			Math::Scalar mz = z_range_mapper.getMappedValue(z);
			Math::Scalar md = d_range_mapper.getMappedValue(d);

			
			Math::Quaternion x_quat(Math::AngleAxis(mx, Math::X_AXIS));
			Math::Quaternion y_quat(Math::AngleAxis(my, Math::Y_AXIS));
			Math::Quaternion z_quat(Math::AngleAxis(mz, Math::Z_AXIS));
			
			Math::Transform transform;
			transform.setOrientation(x_quat * y_quat * z_quat);
			transform.setPosition(desc.instrument_port_position + transform.getOrientation() * desc.instrument_direction * md);
			
			// [TODO] Send transform
		}
		
	}
}