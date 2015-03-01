#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class TransformHolderComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getTypeName()
				{
					return "Interface.TransformHolderComponent";
				}

				virtual Math::Vector3 getPosition() = 0;
				virtual Math::Quaternion getOrientation() = 0;
				virtual Math::Transform getTransform() = 0;
			
		};
	}
}