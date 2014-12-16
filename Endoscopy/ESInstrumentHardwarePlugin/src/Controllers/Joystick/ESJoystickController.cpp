#include <Controllers/Joystick/ESJoystickController.h>

#include <ExportedMessages/InputContext/AddRangeActionMessage.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>


namespace UnknownEngine
{
	namespace Endoscopy
	{
		
		ESJoystickController::ESJoystickController(const char* name, const ESJoystickControllerDesc &desc):
		name(name),
		desc(desc),
		axis_sender(name),
		branches_sender(name)
		{}

		ESJoystickController::~ESJoystickController()
		{}
		
		void ESJoystickController::init ()
		{
			{
				Core::MessageSender<IO::AddRangeActionMessage> sender(name);
				
				IO::AddRangeActionMessage msg;
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.x_axis_action_name;
				msg.action_callback = std::bind(&ESJoystickController::onXAxis, this, std::placeholders::_1);
				sender.sendMessage(msg);
				
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.y_axis_action_name;
				msg.action_callback = std::bind(&ESJoystickController::onYAxis, this, std::placeholders::_1);
				sender.sendMessage(msg);
			}
			{
				Core::MessageSender<IO::AddSimpleActionMessage> sender(name);
				
				IO::AddSimpleActionMessage msg;
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.z_axis_left_rotation_action_name;
				msg.action_callback = std::bind(&ESJoystickController::onZAxisRotatedLeft, this);
				sender.sendMessage(msg);
				
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.z_axis_left_rotation_action_name;
				msg.action_callback = std::bind(&ESJoystickController::onZAxisRotatedLeft, this);
				sender.sendMessage(msg);
				
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.z_axis_right_rotation_action_name;
				msg.action_callback = std::bind(&ESJoystickController::onZAxisRotatedRight, this);
				sender.sendMessage(msg);
				
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.d_axis_push_action_name;
				msg.action_callback = std::bind(&ESJoystickController::onDAxisPushed, this);
				sender.sendMessage(msg);
				
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.d_axis_pull_action_name;
				msg.action_callback = std::bind(&ESJoystickController::onDAxisPulled, this);
				sender.sendMessage(msg);
				
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.branches_moved_together_action_name;
				msg.action_callback = std::bind(&ESJoystickController::onBranchedMovedTogether, this);
				sender.sendMessage(msg);
				
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.branches_moved_apart_action_name;
				msg.action_callback = std::bind(&ESJoystickController::onBranchedMovedApart, this);
				sender.sendMessage(msg);
			}
		}

		void ESJoystickController::shutdown()
		{
		}
		
		ESControllerType ESJoystickController::getType()
		{
			return ESControllerType::JOYSTICK;
		}
		
		void ESJoystickController::onXAxis ( Math::Scalar delta )
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			current_x_delta = delta;
		}

		void ESJoystickController::onYAxis ( Math::Scalar delta )
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			current_y_delta = delta;
		}

		void ESJoystickController::onZAxisRotatedLeft()
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			current_z_delta = -1;
		}

		void ESJoystickController::onZAxisRotatedRight()
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			current_z_delta = 1;
		}

		void ESJoystickController::onDAxisPulled()
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			current_d_delta = -1;
		}

		void ESJoystickController::onDAxisPushed()
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			current_d_delta = 1;
		}
		
		void ESJoystickController::onBranchedMovedApart()
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			current_branches_delta = 1;
		}

		void ESJoystickController::onBranchedMovedTogether()
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			current_branches_delta = -1;
		}
	
		static int sign(int8_t value)
		{
			if(value > 0) return 1;
			else if(value < 0) return -1;
			return 0;
		}
		
		void ESJoystickController::onUpdateFrame(const Core::UpdateFrameMessage &msg)
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			
			Math::Scalar delta = current_x_delta * desc.x_axis_speed * msg.dt;
			if(delta > Math::ZERO_PRECISION)
			{
				current_x_axis += delta;
			}

			delta = current_y_delta * desc.y_axis_speed * msg.dt;
			if(delta > Math::ZERO_PRECISION)
			{
				current_y_axis += delta;
			}
			
			current_z_axis += sign(current_z_delta) * desc.z_axis_speed * msg.dt;
			current_d_axis += sign(current_d_delta) * desc.d_axis_speed * msg.dt;
			current_branches_angle += sign(current_branches_delta) * desc.branches_speed * msg.dt;
			
			{
				ESHardwareOrientationChangedMessage msg;
				msg.instrument_port = instrument_port;
				msg.new_x_axis = current_z_axis;
				msg.new_y_axis = current_y_axis;
				msg.new_z_axis = current_z_axis;
				msg.new_d_axis = current_d_axis;
				axis_sender.sendMessage(msg);
			}
			
			{
				ESHardwareBranchesAngleChangedMessage msg;
				msg.instrument_port = instrument_port;
				msg.new_angle = current_branches_angle;
				branches_sender.sendMessage(msg);
			}
			
		}
		
		const char* ESJoystickController::getName()
		{
			return name.c_str();
		}
		
	}
}