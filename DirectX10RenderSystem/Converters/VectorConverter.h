#pragma once

#ifdef __MINGW32__
#include "MinGWFix.h"
#endif

#include <windows.h>
#include <D3DX10.h>
#include <Vector3.h>

namespace DX10RenderSystem
{

	class VectorConverter
	{
		public:

			static UnknownEngine::Math::Vector3 fromDxVector ( const D3DXVECTOR3 &dxVector );
			static D3DXVECTOR3 toDxVector ( const UnknownEngine::Math::Vector3 &vector );

	};

}
