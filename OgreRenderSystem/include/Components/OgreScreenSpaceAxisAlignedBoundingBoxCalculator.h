#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/RenderSystem/Common/IScreenSpaceAxisAlignedBoundingBoxCalculator.h>
#include <ComponentInterfaces/RenderSystem/Common/IScreenSpaceCoordinatesCalculator.h>
#include <ComponentSystem/ComponentInterfacePtr.h>

namespace UnknownEngine
{
    namespace Graphics
    {
        class OgreScreenSpaceAxisAlignedBoundingBoxCalculator :
                public Core::BaseComponent,
                public ComponentInterfaces::IScreenSpaceAxisAlignedBoundingBoxCalculator
        {
        public:
            OgreScreenSpaceAxisAlignedBoundingBoxCalculator(const char* name, OgreScreenSpaceAxisAlignedBoundingBoxCalculatorDesc &desc);

            virtual AxisAlignedBoundingBox calculateScreenSpaceAxisAlignedBoundingBox(ComponentInterfaces::IRenderable *renderable) override;

            virtual Core::IComponentInterface *getInterface(const Core::ComponentType &type) override;

            virtual bool init() override;

            virtual void shutdown() override;

            virtual Core::ComponentType getType() const override {return getTypeName(); }
            constexpr static const char* getTypeName(){return "OgreScreenSpaceAxisAlignedBoundingBoxCalculator";}

        private:
            Core::ComponentInterfacePtr<ComponentInterfaces::IScreenSpaceCoordinatesCalculator> screen_space_coordinates_calculator;
        };

    }
}