#pragma once

#include <Components/OgreScreenSpaceAxisAlignedBoundingBoxCalculator.h>
#include <ComponentInterfaces/RenderSystem/Common/IRenderable.h>
#include <AxisAlignedBoundingBox.h>

namespace UnknownEngine
{
    namespace Graphics
    {
        OgreScreenSpaceAxisAlignedBoundingBoxCalculator::OgreScreenSpaceAxisAlignedBoundingBoxCalculator(const char* name, OgreScreenSpaceAxisAlignedBoundingBoxCalculatorDesc &desc):
        Core::BaseComponent(name),
        screen_space_coordinates_calculator(nullptr)
        {

        }

        virtual AxisAlignedBoundingBox OgreScreenSpaceAxisAlignedBoundingBoxCalculator::calculateScreenSpaceAxisAlignedBoundingBox(ComponentInterfaces::IRenderable *renderable) override
        {
            AxisAlignedBoundingBox 3dBox = renderable->getAxisAlignedBoundingBox();
            return 3dBox;
        }

        virtual Core::IComponentInterface* OgreScreenSpaceAxisAlignedBoundingBoxCalculator::getInterface(const Core::ComponentType &type) override
        {
            if(type == ComponentInterfaces::IScreenSpaceAxisAlignedBoundingBoxCalculator::getType()) {
                return static_cast<ComponentInterfaces::IScreenSpaceAxisAlignedBoundingBoxCalculator*>(this);
            }
            return nullptr;
        }

        virtual bool OgreScreenSpaceAxisAlignedBoundingBoxCalculator::init() override
        {

        }

        virtual void OgreScreenSpaceAxisAlignedBoundingBoxCalculator::shutdown() override
        {

        }

    }
}

