#pragma once

#include <algorithm>
#include <Vectors/Vector3.h>

namespace UnknownEngine
{
	namespace Math
	{
		class Vector3Utils
		{
		public:
			static void selectMaxComponentValues(const Math::Vector3 &vector1, const Math::Vector3 &vector2, Math::Vector3 &out_result)
			{
				out_result.setX(std::max(vector1.x(), vector2.x()));
				out_result.setY(std::max(vector1.y(), vector2.y()));
				out_result.setZ(std::max(vector1.z(), vector2.z()));
			}
			
			static void selectMinComponentValues(const Math::Vector3 &vector1, const Math::Vector3 &vector2, Math::Vector3 &out_result)
			{
				out_result.setX(std::min(vector1.x(), vector2.x()));
				out_result.setY(std::min(vector1.y(), vector2.y()));
				out_result.setZ(std::min(vector1.z(), vector2.z()));
			}
		};
	}
}