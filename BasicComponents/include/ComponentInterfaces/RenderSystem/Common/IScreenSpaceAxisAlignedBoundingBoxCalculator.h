#pragma once

#include <AxisAlignedBoundingBox.h>
#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
    namespace ComponentInterfaces
    {
        class IRenderable;

        class IScreenSpaceAxisAlignedBoundingBoxCalculator : public Core::IComponentInterface
        {
        public:
            constexpr static const char* getType(){return "IScreenSpaceBoundingBoxCalculator";}

            virtual Math::AxisAlignedBoundingBox calculateScreenSpaceAxisAlignedBoundingBox(IRenderable* renderable) = 0;
        };
    }
}