#include "MeshDataTypes.h"

using namespace UnknownEngine;
using namespace UnknownEngine::Util;

Math::Vector3 VertexType::getPosition () const
{
	return position;
}

Math::Vector3 VertexType::getNormal () const throw ( NoSuchVertexElementException )
{
	if ( this->hasNormal() )
	{
		return normal;
	}

	throw NoSuchVertexElementException( NORMAL_NAME );
}

Math::Vector3 VertexType::getTangent () const throw ( NoSuchVertexElementException )
{
	if ( this->hasTangent() )
	{
		return tangent;
	}

	throw NoSuchVertexElementException( TANGENT_NAME );
}

TextureCoordinateType VertexType::getTextureCoordinate () const throw ( NoSuchVertexElementException )
{
	if ( this->hasTextureCoordinate() )
	{
		return texture_coordinate;
	}

	throw NoSuchVertexElementException( TEXTURE_COORDINATE_NAME );
}

void VertexType::setPosition ( const Math::Vector3& position )
{
}

void VertexType::setNormal ( const Math::Vector3& normal )
{
}

void VertexType::setTangent ( const Math::Vector3& tangent )
{
}

void VertexType::setTextureCoordinate ( const TextureCoordinateType& position )
{
}

bool VertexType::hasNormal () const
{
	return has_normal;
}

bool VertexType::hasTangent () const
{
	return has_tangent;
}

bool VertexType::hasTextureCoordinate () const
{
	return has_texture_coordinate;
}
