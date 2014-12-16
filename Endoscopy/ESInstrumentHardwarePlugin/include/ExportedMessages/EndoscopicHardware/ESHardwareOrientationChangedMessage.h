#pragma once

#include <ESInstrumentPort.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		struct ESHardwareOrientationChangedMessage
		{
			constexpr static const char* getTypeName(){return "Endoscopy.Hardware.OrientationChanged";}
			
			ESInstrumentPort instrument_port;
			Math::Scalar new_x_axis;
			Math::Scalar new_y_axis;
			Math::Scalar new_z_axis;
			Math::Scalar new_d_axis;
		};
	}
}