#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class UpdateFrameListenerComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType()
				{
					return "UpdateFrameListenerComponent";
				}
				
				virtual void onUpdateFrame(Math::Scalar dt) = 0;
		};
	}
}
