#include <Converters/VectorConverter.h>

using namespace UnknownEngine;
using namespace DX10RenderSystem;

Math::Vector3 VectorConverter::fromDxVector ( const D3DXVECTOR3 &dxVector )
{
	return Math::Vector3( dxVector.x, dxVector.y, dxVector.z );
}

D3DXVECTOR3 VectorConverter::toDxVector ( const Math::Vector3 &vector )
{
	return D3DXVECTOR3( vector.x(), vector.y(), vector.z() );
}
