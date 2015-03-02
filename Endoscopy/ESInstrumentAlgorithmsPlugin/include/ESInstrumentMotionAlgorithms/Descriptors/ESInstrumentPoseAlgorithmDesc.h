#pragma once

#include <Scalar.h>
#include <Vectors/Vector3.h>
#include <ESInstrumentPort.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Endoscopy
	{
		struct ESInstrumentPoseAlgorithmDesc
		{
			Math::Scalar lower_x;
			Math::Scalar higher_x;
			Math::Scalar lower_y;
			Math::Scalar higher_y;
			Math::Scalar lower_z;
			Math::Scalar higher_z;
			Math::Scalar lower_d;
			Math::Scalar higher_d;
			
			Math::Vector3 instrument_port_position;
			Math::Vector3 instrument_direction;

			Core::IComponent* hardware_controller;
			
			ESInstrumentPoseAlgorithmDesc():
			instrument_direction(Math::X_AXIS),
			hardware_controller(nullptr)
			{
			}
		};
	}
}