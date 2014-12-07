#pragma once

#include <Scalar.h>
#include <Transform/Transform.h>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		class PxMaterialDataProvider;
		
		UNKNOWNENGINE_ALIGNED_STRUCT(16) PxBoxShapeDataProviderDesc
		{
			PxMaterialDataProvider *material;
			Math::Transform pose_offset;
			Math::Scalar width;
			Math::Scalar height;
			Math::Scalar depth;
			bool is_exclusive;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
			PxBoxShapeDataProviderDesc():
			is_exclusive(false)
			{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Physics::PxBoxShapeDataProviderDesc);