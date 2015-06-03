#pragma once

#include <ComponentSystem/IComponentInterface.h>

#include <Vectors/Vector2.h>
#include <Vectors/Vector3.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IScreenSpaceCoordinatesCalculator
		{
			public:
				constexpr static const char* getType()
				{
					return "IScreenSpaceCoordinatesCalculator";
				}

				virtual Math::Vector3 getScreenSpaceCoordinate(const Math::Vector3 &world_coordinate) = 0;
		};
	}
}
