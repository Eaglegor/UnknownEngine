#pragma once

#include <MessageSystem/Message.h>
#include <ESInstrumentPort.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		struct ESHardwareBranchesAngleChangedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Endoscopy.Hardware.BranchedAngleChanged";}
			
			ESInstrumentPort instrument_port;
			Math::Scalar new_angle;
		};
	}
}