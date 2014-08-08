#pragma once

#include <vector>
#include <Vectors/Vector3.h>
#include <Mesh/MeshDataTypes.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{

	namespace Utils
	{

		class MeshData
		{
			public:
				UNKNOWNENGINE_INLINE
				virtual const std::vector<VertexType>& getVertices () const
				{
					return vertices;
				}

				UNKNOWNENGINE_INLINE
				virtual const std::vector<IndexType>& getIndices () const
				{
					return indices;
				}

				UNKNOWNENGINE_INLINE
				virtual std::vector<VertexType>& getVertices ()
				{
					return vertices;
				}

				UNKNOWNENGINE_INLINE
				virtual std::vector<IndexType>& getIndices ()
				{
					return indices;
				}

				virtual ~MeshData ()
				{
				}
			private:
				std::vector<VertexType> vertices;
				std::vector<IndexType> indices;

		};

		typedef MeshData* MeshDataPtr;

	}

}
