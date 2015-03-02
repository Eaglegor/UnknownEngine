#include <ESInstrumentMotionAlgorithms/Components/ESInstrumentPoseAlgorithm.h>
#include <ESHardwareEvents/ESHardwareStickPoseChangedEvent.h>
#include <ValueRangeMapper.h>
#include <Transform/Transform.h>
#include <ComponentInterfaces/Transform/MovableComponent.h>

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
		d_range_mapper(-1, 1, -RANGE_VALUE, RANGE_VALUE*10),
		hardware_controller(desc.hardware_controller)
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
			if(!hardware_controller) return false;
			hardware_controller->addListener(this);
			return true;
		}

		void ESInstrumentPoseAlgorithm::shutdown()
		{
			hardware_controller->removeListener(this);
		}

		void ESInstrumentPoseAlgorithm::onBranchesAngleChangedEvent ( const ESHardwareBranchesAngleChangedEvent& evt )
		{
			// Branches not supported by the pose algorithm
		}

		void ESInstrumentPoseAlgorithm::onHardwareStickPoseChanged ( const ESHardwareStickPoseChangedEvent& evt )
		{
			Math::Scalar mx = x_range_mapper.getMappedValue(evt.x);
			Math::Scalar my = y_range_mapper.getMappedValue(evt.y);
			Math::Scalar mz = z_range_mapper.getMappedValue(evt.z);
			Math::Scalar md = d_range_mapper.getMappedValue(evt.d);
			
			Math::Quaternion x_quat(Math::AngleAxis(mx, Math::X_AXIS));
			Math::Quaternion y_quat(Math::AngleAxis(my, Math::Y_AXIS));
			Math::Quaternion z_quat(Math::AngleAxis(mz, Math::Z_AXIS));
			
			Math::Transform transform;
			transform.setOrientation(x_quat * y_quat * z_quat);
			transform.setPosition(desc.instrument_port_position + transform.getOrientation() * desc.instrument_direction * md);
			
			for(ComponentInterfaces::MovableComponent* listener : transform_listeners)
			{
				listener->setTransform(transform);
			}
		}

		void ESInstrumentPoseAlgorithm::addListener ( ComponentInterfaces::MovableComponent* movable_component )
		{
			transform_listeners.emplace(movable_component);
		}

		void ESInstrumentPoseAlgorithm::removeListener ( ComponentInterfaces::MovableComponent* movable_component )
		{
			transform_listeners.erase(movable_component);
		}
	
		Core::IComponentInterface* ESInstrumentPoseAlgorithm::getInterface ( const Core::ComponentType& type )
		{
			using namespace ComponentInterfaces;
			if(type == TransformNotifierComponent::getTypeName()) return static_cast<TransformNotifierComponent*>(this);
			return nullptr;
		}
	
	}
}