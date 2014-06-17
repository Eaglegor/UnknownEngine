#pragma once

#include "Scalar.h"

namespace UnknownEngine
{
	namespace Math
	{
		class Vector3
		{
		public:
			Vector3(void);
			Vector3(Scalar x, Scalar y, Scalar z);
			Vector3(const Vector3 &rvalue);
			virtual ~Vector3(void);

			inline Scalar x() const { return values[0]; }
			inline Scalar y() const { return values[1]; }
			inline Scalar z() const { return values[2]; }

			inline void setX(Scalar x) { values[0] = x; }
			inline void setY(Scalar y) { values[1] = y; }
			inline void setZ(Scalar z) { values[2] = z; }

			inline void setValues(Scalar x, Scalar y, Scalar z);
			inline const Scalar* getRawValues() const { return values; };

		private:
			Scalar values[4];

		};
	

	}
}