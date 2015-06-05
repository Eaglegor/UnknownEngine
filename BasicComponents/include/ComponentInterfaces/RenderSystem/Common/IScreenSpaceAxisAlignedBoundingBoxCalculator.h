#pragma once

#include <AxisAlignedBoundingBox.h>

namespace UnknownEngine
{
    namespace ComponentInterfaces
    {
        class IRenderable;

        class IScreenSpaceAxisAlignedBoundingBoxCalculator
        {
        public:
            constexpr static const char* getType(){return "IScreenSpaceBoundingBoxCalculator";}

            virtual AxisAlignedBoundingBox calculateScreenSpaceAxisAlignedBoundingBox(IRenderable* renderable) = 0;
        };
    }
}