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
			PxMaterialDataProvider *material; // Shape material
			Core::Transform pose_offset; // Pose offset
			Math::Scalar width; // X
			Math::Scalar height; // Y
			Math::Scalar depth; // Z
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Physics::PxBoxShapeDataProviderDesc);