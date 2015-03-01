#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESHardwareStateListener : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getTypeName(){ return "IESHardwareStateListener"; }
			
			virtual void onHardwareStateUpdate(Math::Scalar x, Math::Scalar y, Math::Scalar z, Math::Scalar d) = 0;
		};
	}
}