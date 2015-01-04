#pragma once

#include <Controllers/IESController.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/EndoscopicHardware/ESHardwareOrientationChangedMessage.h>
#include <ExportedMessages/EndoscopicHardware/ESHardwareBranchesAngleChangedMessage.h>
#include <Controllers/Joystick/ESJoystickControllerDesc.h>
#include <mutex>

namespace UnknownEngine
{
	namespace Core
	{

		struct UpdateFrameMessage;
		class BaseMessageListener;
	}

	namespace Endoscopy
	{
		class ESJoystickController : public IESController
		{
		public:
			ESJoystickController(const char* name, const ESJoystickControllerDesc &desc);
			virtual ~ESJoystickController();
			
			virtual void init();
			virtual void shutdown();
			
			virtual ESControllerType getType();
			virtual const char* getName();
			
		private:
			std::string name;
			void onXAxis(Math::Scalar delta);
			void onYAxis(Math::Scalar delta);
			void onZAxisRotatedLeft();
			void onZAxisRotatedRight();
			void onDAxisPushed();
			void onDAxisPulled();
			void onBranchedMovedTogether();
			void onBranchedMovedApart();
			void onUpdateFrame(const Core::UpdateFrameMessage &msg);
			
			ESJoystickControllerDesc desc;

			ESInstrumentPort instrument_port;
			
			Core::MessageSender<ESHardwareOrientationChangedMessage> axis_sender;
			Core::MessageSender<ESHardwareBranchesAngleChangedMessage> branches_sender;
			
			Math::Scalar current_x_delta;
			Math::Scalar current_y_delta;
			int8_t current_z_delta;
			int8_t current_d_delta;
			int8_t current_branches_delta;
			
			Math::Scalar current_x_axis;
			Math::Scalar current_y_axis;
			Math::Scalar current_z_axis;
			Math::Scalar current_d_axis;
			Math::Scalar current_branches_angle;

			std::unique_ptr<Core::BaseMessageListener> listener;
			
			typedef std::mutex LockPrimitive;
			LockPrimitive mutex;
			
		};
	}
}