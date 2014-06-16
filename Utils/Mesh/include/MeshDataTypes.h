#pragma once

#include <vector>
#include <string>
#include <Vector3.h>

namespace UnknownEngine
{

	namespace Util
	{

		typedef unsigned long IndexType;
		typedef float TextureCoordinateType;

		const std::string TANGENT_NAME = "Tangent";
		const std::string NORMAL_NAME = "Normal";
		const std::string TEXTURE_COORDINATE_NAME = "Texture coordinate";

		class NoSuchVertexElementException: public std::exception
		{
			public:
				NoSuchVertexElementException ( std::string element_name ) throw ()
				{
					reason = "Vertex has no element: " + element_name;
				}

				const char* what () const throw () override
				{
					return reason.c_str();
				}
				~NoSuchVertexElementException () throw ()
				{
				}
			private:
				std::string reason;
		};

		class VertexType
		{

			public:
				Math::Vector3 getPosition () const;
				Math::Vector3 getNormal () const throw ( NoSuchVertexElementException );
				Math::Vector3 getTangent () const throw ( NoSuchVertexElementException );
				TextureCoordinateType getTextureCoordinate () const throw ( NoSuchVertexElementException );

				void setPosition ( const Math::Vector3 &position );
				void setNormal ( const Math::Vector3 &normal );
				void setTangent ( const Math::Vector3 &tangent );
				void setTextureCoordinate ( const TextureCoordinateType &position );

				bool hasNormal () const;
				bool hasTangent () const;
				bool hasTextureCoordinate () const;

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
