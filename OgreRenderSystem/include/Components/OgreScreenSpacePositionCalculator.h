#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <Descriptors/Components/OgreScreenSpaceCoordinatesCalculatorDesc.h>
#include <ComponentInterfaces/RenderSystem/Common/IScreenSpaceCoordinatesCalculator.h>
#include <ComponentInterfaces/RenderSystem/Ogre/IOgreCameraComponent.h>
#include <Converters/OgreVector3Converter.h>
#include <OgreCamera.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreScreenSpacePositionCalculator:
		public Core::BaseComponent,
		public ComponentInterfaces::IScreenSpaceCoordinatesCalculator
		{
			public:

				OgreScreenSpacePositionCalculator ( const char* name, const OgreScreenSpaceCoordinatesCalculatorDesc &desc);

				constexpr static const char* getTypeName(){return "Ogre.ScreenSpaceCoordinatesCalculator";}
 				virtual Core::ComponentType getType() const override {return getTypeName();}
				
				virtual Core::IComponentInterface * getInterface ( const Core::ComponentType & type ) override;

				virtual bool init() override{
					if(!camera) return false;
					return true;
				}
				virtual void shutdown() override{}

				virtual Math::Vector3 getScreenSpaceCoordinate(const Math::Vector3 &world_coordinate) override;

			private:
				Core::ComponentInterfacePtr<ComponentInterfaces::IOgreCameraComponent> camera;
				OgreScreenSpaceCoordinatesCalculatorDesc desc;
		};

	} // namespace Graphics
} // namespace UnknownEngine
