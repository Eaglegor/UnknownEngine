#pragma once

#include <vector>
#include <string>
#include <Vectors/Vector3.h>
#include <InlineSpecification.h>
#include <Exception.h>
#include <AlignedNew.h>

namespace UnknownEngine
{

	namespace Utils
	{

		typedef unsigned long IndexType;

		class TextureCoordinateType: private Math::Vector3
		{
			public:
				TextureCoordinateType(const Scalar& u, const Scalar &v, const Scalar &w):Math::Vector3(u,v,w)
				{}
				
				TextureCoordinateType(){}
				
				UNKNOWNENGINE_INLINE
				float u() const
				{
					return x();
				}

				UNKNOWNENGINE_INLINE
				float v() const
				{
					return y();
				}

				UNKNOWNENGINE_INLINE
				float w() const
				{
					return z();
				}

				UNKNOWNENGINE_INLINE
				void setU ( float u )
				{
					setX ( u );
				}

				UNKNOWNENGINE_INLINE
				void setV ( float v )
				{
					setY ( v );
				}

				UNKNOWNENGINE_INLINE
				void setW ( float w )
				{
					setZ ( w );
				}
		};

		const std::string TANGENT_NAME = "Tangent";
		const std::string BINORMAL_NAME = "Binormal";
		const std::string NORMAL_NAME = "Normal";
		const std::string TEXTURE_COORDINATE_NAME = "Texture coordinate";

		UNKNOWNENGINE_SIMPLE_EXCEPTION ( NoSuchVertexElementException );

		UNKNOWNENGINE_ALIGNED_CLASS(16) VertexType
		{

			public:

				VertexType():
				has_normal(false),
				has_tangent(false),
				has_texture_coordinate(false)
				{}
				
				UNKNOWNENGINE_INLINE
				Math::Vector3 getPosition() const
				{
					return position;
				}

				UNKNOWNENGINE_INLINE
				Math::Vector3 getNormal() const 
				{
					if ( this->hasNormal() )
					{
						return normal;
					}

					throw NoSuchVertexElementException ( NORMAL_NAME );
				}

				UNKNOWNENGINE_INLINE
				Math::Vector3 getTangent() const 
				{
					if ( this->hasTangent() )
					{
						return tangent;
					}

					throw NoSuchVertexElementException ( TANGENT_NAME );
				}

				UNKNOWNENGINE_INLINE
				Math::Vector3 getBinormal() const 
				{
					if ( this->hasBinormal() )
					{
						return binormal;
					}

					throw NoSuchVertexElementException ( BINORMAL_NAME );
				}
				
				UNKNOWNENGINE_INLINE
				TextureCoordinateType getTextureCoordinate() const 
				{
					if ( this->hasTextureCoordinate() )
					{
						return texture_coordinate;
					}

					throw NoSuchVertexElementException ( TEXTURE_COORDINATE_NAME );
				}

				UNKNOWNENGINE_INLINE
				void setPosition ( const Math::Vector3& position )
				{
					this->position = position;
				}

				UNKNOWNENGINE_INLINE
				void setNormal ( const Math::Vector3& normal )
				{
					this->normal = normal;
					this->has_normal = true;
				}

				UNKNOWNENGINE_INLINE
				void setTangent ( const Math::Vector3& tangent )
				{
					this->tangent = tangent;
					this->has_tangent = true;
				}

				UNKNOWNENGINE_INLINE
				void setBinormal ( const Math::Vector3& binormal )
				{
					this->binormal = binormal;
					this->has_binormal = true;
				}
				
				UNKNOWNENGINE_INLINE
				void setTextureCoordinate ( const TextureCoordinateType& texture_coordinate )
				{
					this->texture_coordinate = texture_coordinate;
					this->has_texture_coordinate = true;
				}

				UNKNOWNENGINE_INLINE
				bool hasNormal() const
				{
					return has_normal;
				}

				UNKNOWNENGINE_INLINE
				bool hasTangent() const
				{
					return has_tangent;
				}

				UNKNOWNENGINE_INLINE
				bool hasBinormal() const
				{
					return has_binormal;
				}
				
				UNKNOWNENGINE_INLINE
				bool hasTextureCoordinate() const
				{
					return has_texture_coordinate;
				}

				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
				
			private:
				Math::Vector3 position;

				Math::Vector3 normal;
				bool has_normal;

				Math::Vector3 tangent;
				bool has_tangent;

				Math::Vector3 binormal;
				bool has_binormal;
				
				TextureCoordinateType texture_coordinate;
				bool has_texture_coordinate;
		};

	}

}