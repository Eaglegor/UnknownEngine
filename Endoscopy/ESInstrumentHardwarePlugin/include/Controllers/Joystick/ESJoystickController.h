#pragma once

#include <Controllers/IESController.h>
#include <Controllers/Joystick/ESJoystickControllerDesc.h>
#include <mutex>

#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentInterfaces/Input/Common/IContextualActionsMapper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <Concurrency/DataStructures/LockingConcurrentSet.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseMessageListener;
	}

	namespace Endoscopy
	{
		class ESJoystickController : 
		public IESController, 
		public ComponentInterfaces::UpdateFrameListenerComponent
		{
		public:
			ESJoystickController(const char* name, const ESJoystickControllerDesc &desc);
			virtual ~ESJoystickController();
			
			virtual void init();
			virtual void shutdown();
			
			virtual ESControllerType getType();
			virtual const char* getName();
			
			virtual void addListener ( ComponentInterfaces::ESHardwareStateListener* listener ) override;
			virtual void removeListener ( ComponentInterfaces::ESHardwareStateListener* listener ) override;
			
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
			
			virtual void onUpdateFrame ( Math::Scalar dt ) override;
			
			ESJoystickControllerDesc desc;

			//ESInstrumentPort instrument_port;

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

			typedef std::mutex LockPrimitive;
			LockPrimitive mutex;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
			Core::ComponentInterfacePtr<ComponentInterfaces::IContextualActionsMapper> input_context_mapping_provider;
			
			Utils::LockingConcurrentSet<ComponentInterfaces::ESHardwareStateListener*> listeners;
			
		};
	}
}