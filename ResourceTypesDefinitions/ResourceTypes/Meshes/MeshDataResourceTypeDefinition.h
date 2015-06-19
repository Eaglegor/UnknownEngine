#pragma once

#include <ResourceManager/ResourceTypeMetaInfo.h>
#include <Mesh/MeshData.h>

namespace UnknownEngine
{
	namespace Resources
	{
		template<>
		class ResourceTypeMetaInfo<Utils::MeshData> : public IResourceTypeMetaInfo
		{
		public:
			virtual ResourceType getType() { return staticGetType(); }
			virtual ResourceType staticGetType() { return "Engine.MeshData"; }
		};
	}
}
