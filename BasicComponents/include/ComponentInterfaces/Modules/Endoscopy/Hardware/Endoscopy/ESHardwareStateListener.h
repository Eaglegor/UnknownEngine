#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		struct ESHardwareStickPoseChangedEvent;
		struct ESHardwareBranchesAngleChangedEvent;
	}
	
	namespace ComponentInterfaces
	{
		class ESHardwareStateListener : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){ return "ESHardwareStateListener"; }
			
			virtual void onHardwareStickPoseChanged(const Endoscopy::ESHardwareStickPoseChangedEvent& evt) = 0;
			virtual void onBranchesAngleChangedEvent(const Endoscopy::ESHardwareBranchesAngleChangedEvent& evt) = 0;
		};
	}
}