#include <Controllers/Joystick/ESJoystickController.h>

#include <ExportedMessages/InputContext/AddRangeActionMessage.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageSystem/BaseMessageListener.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>


namespace UnknownEngine
{
	namespace Endoscopy
	{
		
		ESJoystickController::ESJoystickController(const char* name, const ESJoystickControllerDesc &desc):
		name(name),
		desc(desc),
		update_frame_provider(desc.update_frame_provider),
		input_context_mapping_provider(desc.input_context_mapping_provider)
		{}

		ESJoystickController::~ESJoystickController()
		{}
		
		void ESJoystickController::init ()
		{
			if(input_context_mapping_provider)
			{
				const char* context_name = desc.input_context_name.c_str();

				{
					const char* action_name = desc.x_axis_action_name.c_str();
					auto action_callback = std::bind(&ESJoystickController::onXAxis, this, std::placeholders::_1);
					input_context_mapping_provider->addRangedAction(context_name, action_name, action_callback);
				}

				{
					const char* action_name = desc.y_axis_action_name.c_str();
					auto action_callback = std::bind(&ESJoystickController::onYAxis, this, std::placeholders::_1);
					input_context_mapping_provider->addRangedAction(context_name, action_name, action_callback);
				}

				{
					const char* action_name = desc.z_axis_left_rotation_action_name.c_str();
					auto action_callback = std::bind(&ESJoystickController::onZAxisRotatedLeft, this);
					input_context_mapping_provider->addSimpleAction(context_name, action_name, action_callback);
				}

				{
					const char* action_name = desc.z_axis_right_rotation_action_name.c_str();
					auto action_callback = std::bind(&ESJoystickController::onZAxisRotatedRight, this);
					input_context_mapping_provider->addSimpleAction(context_name, action_name, action_callback);
				}

				{
					const char* action_name = desc.d_axis_push_action_name.c_str();
					auto action_callback = std::bind(&ESJoystickController::onDAxisPushed, this);
					input_context_mapping_provider->addSimpleAction(context_name, action_name, action_callback);
				}

				{
					const char* action_name = desc.d_axis_pull_action_name.c_str();
					auto action_callback = std::bind(&ESJoystickController::onDAxisPulled, this);
					input_context_mapping_provider->addSimpleAction(context_name, action_name, action_callback);
				}

				{
					const char* action_name = desc.branches_moved_together_action_name.c_str();
					auto action_callback = std::bind(&ESJoystickController::onBranchedMovedTogether, this);
					input_context_mapping_provider->addSimpleAction(context_name, action_name, action_callback);
				}

			}

			if(update_frame_provider) update_frame_provider->addListener(this);
			
		}

		void ESJoystickController::shutdown()
		{
			if(update_frame_provider) update_frame_provider->removeListener(this);

			if(input_context_mapping_provider)
			{
				const char* context_name = desc.input_context_name.c_str();

				{
					const char* action_name = desc.x_axis_action_name.c_str();
					input_context_mapping_provider->removeRangedAction(context_name, action_name);
				}

				{
					const char* action_name = desc.y_axis_action_name.c_str();
					input_context_mapping_provider->removeRangedAction(context_name, action_name);
				}

				{
					const char* action_name = desc.z_axis_left_rotation_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(context_name, action_name);
				}

				{
					const char* action_name = desc.z_axis_right_rotation_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(context_name, action_name);
				}

				{
					const char* action_name = desc.d_axis_push_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(context_name, action_name);
				}

				{
					const char* action_name = desc.d_axis_pull_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(context_name, action_name);
				}

				{
					const char* action_name = desc.branches_moved_together_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(context_name, action_name);
				}
			}
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

		void ESJoystickController::onUpdateFrame ( Math::Scalar dt )
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			
			Math::Scalar delta = current_x_delta * desc.x_axis_speed * dt;
			if(std::fabs(delta) > Math::ZERO_PRECISION)
			{
				current_x_axis += delta;
			}
			
			delta = current_y_delta * desc.y_axis_speed * dt;
			if(std::fabs(delta) > Math::ZERO_PRECISION)
			{
				current_y_axis -= delta;
			}
			
			current_z_axis += sign(current_z_delta) * desc.z_axis_speed * dt;
			current_d_axis += sign(current_d_delta) * desc.d_axis_speed * dt;
			current_branches_angle += sign(current_branches_delta) * desc.branches_speed * dt;
			
			if(current_x_axis < desc.x_low_limit) current_x_axis = desc.x_low_limit;
			if(current_x_axis > desc.x_high_limit) current_x_axis = desc.x_high_limit;
			
			if(current_y_axis < desc.y_low_limit) current_y_axis = desc.y_low_limit;
			if(current_y_axis > desc.y_high_limit) current_y_axis = desc.y_high_limit;
			
			if(current_d_axis < desc.d_low_limit) current_d_axis = desc.d_low_limit;
			if(current_d_axis > desc.d_high_limit) current_d_axis = desc.d_high_limit;
			
			/*{
				ESHardwareOrientationChangedMessage msg;
				msg.instrument_port = instrument_port;
				msg.new_x_axis = current_x_axis;
				msg.new_y_axis = current_y_axis;
				msg.new_z_axis = current_z_axis;
				msg.new_d_axis = current_d_axis;
				axis_sender.sendMessage(msg);
			}*/
			
			/*{
				ESHardwareBranchesAngleChangedMessage msg;
				msg.instrument_port = instrument_port;
				msg.new_angle = current_branches_angle;
				branches_sender.sendMessage(msg);
			}*/

			current_z_delta = 0;
			current_d_delta = 0;
		}
		
		const char* ESJoystickController::getName()
		{
			return name.c_str();
		}
		
	}
}