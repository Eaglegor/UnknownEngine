#include "Vector3.h"

using namespace UnknownEngine::Math;

Vector3::Vector3 ( void )
{
	setValues( 0, 0, 0 );
	values[3] = 1.0f;
}

Vector3::Vector3 ( Scalar x, Scalar y, Scalar z )
{
	setValues( x, y, z );
	values[3] = 1.0f;
}

Vector3::Vector3 ( const Vector3 &rvalue )
{
	setValues( rvalue.x(), rvalue.y(), rvalue.z() );
	values[3] = 1.0f;
}

void Vector3::setValues ( Scalar x, Scalar y, Scalar z )
{
	values[0] = x;
	values[1] = y;
	values[2] = z;
}

Vector3::~Vector3 ( void )
{
}
