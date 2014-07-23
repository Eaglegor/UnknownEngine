#pragma once

#include <vector>
#include <string>
#include <Vectors/Vector3.h>
#include <InlineSpecification.h>
#include <Exception.h>

namespace UnknownEngine
{

	namespace Utils
	{

		typedef unsigned long IndexType;

		class TextureCoordinateType: private Math::Vector3
		{
			public:
				UNKNOWNENGINE_INLINE
				float u(){return x();}

				UNKNOWNENGINE_INLINE
				float v(){return y();}

				UNKNOWNENGINE_INLINE
				float w(){return w();}

				UNKNOWNENGINE_INLINE
				float setU(float u){ setX(u); }

				UNKNOWNENGINE_INLINE
				float setV(float v){ setY(v); }

				UNKNOWNENGINE_INLINE
				float setW(float w){ setZ(w); }
		};

		const std::string TANGENT_NAME = "Tangent";
		const std::string NORMAL_NAME = "Normal";
		const std::string TEXTURE_COORDINATE_NAME = "Texture coordinate";

		UNKNOWNENGINE_SIMPLE_EXCEPTION(NoSuchVertexElementException);

		class VertexType
		{

			public:

				UNKNOWNENGINE_INLINE
				Math::Vector3 getPosition() const
				{
					return position;
				}

				UNKNOWNENGINE_INLINE
				Math::Vector3 getNormal() const throw (NoSuchVertexElementException)
				{
					if (this->hasNormal())
					{
						return normal;
					}

					throw NoSuchVertexElementException(NORMAL_NAME);
				}

				UNKNOWNENGINE_INLINE
				Math::Vector3 getTangent() const throw (NoSuchVertexElementException)
				{
					if (this->hasTangent())
					{
						return tangent;
					}

					throw NoSuchVertexElementException(TANGENT_NAME);
				}

				UNKNOWNENGINE_INLINE
				TextureCoordinateType getTextureCoordinate() const throw (NoSuchVertexElementException)
				{
					if (this->hasTextureCoordinate())
					{
						return texture_coordinate;
					}

					throw NoSuchVertexElementException(TEXTURE_COORDINATE_NAME);
				}

				UNKNOWNENGINE_INLINE
				void setPosition(const Math::Vector3& position)
				{
				}

				UNKNOWNENGINE_INLINE
				void setNormal(const Math::Vector3& normal)
				{
				}

				UNKNOWNENGINE_INLINE
				void setTangent(const Math::Vector3& tangent)
				{
				}

				UNKNOWNENGINE_INLINE
				void setTextureCoordinate(const TextureCoordinateType& position)
				{
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
				bool hasTextureCoordinate() const
				{
					return has_texture_coordinate;
				}

			private:
				Math::Vector3 position;

				Math::Vector3 normal;
				bool has_normal;

				Math::Vector3 tangent;
				bool has_tangent;

				TextureCoordinateType texture_coordinate;
				bool has_texture_coordinate;
		};

	}

}
