#pragma once

#include <vector>
#include <Vectors/Vector3.h>
#include <Mesh/MeshDataTypes.h>

namespace UnknownEngine
{

	namespace Util
	{

		class MeshData
		{
			public:
				virtual std::vector<VertexType> getVertices () = 0;
				virtual std::vector<IndexType> getIndices () = 0;

				virtual ~MeshData ()
				{
				}
		};

	}

}
