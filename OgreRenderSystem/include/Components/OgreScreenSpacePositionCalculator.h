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

				OgreScreenSpacePositionCalculator ( const char* name, const OgreScreenSpaceCoordinatesCalculatorDesc &desc):
				Core::BaseComponent(name),
				camera(desc.camera)
				{}

				virtual ~OgreScreenSpacePositionCalculator(){}

				constexpr static const char* getTypeName(){return "Ogre.ScreenSpaceCoordinatesCalculator";}
 				virtual Core::ComponentType getType() const override {return getTypeName();}
				
				virtual IComponentInterface * getInterface ( const Core::ComponentType & type ) override
				{
					if(type == ComponentInterfaces::IScreenSpaceCoordinatesCalculator::getType()){
						return static_cast<ComponentInterfaces::IScreenSpaceCoordinatesCalculator>(this);
					}
					return nullptr;
				}

				virtual void init() override{}
				virtual void shutdown() override{}

				virtual Math::Vector3 getScreenSpaceCoordinate(const Math::Vector3 &world_coordinate) override
				{
					return OgreVector3Converter::fromOgreVector(camera->getOgreCamera()->getProjectionMatrix() * camera->getOgreCamera()->getViewMatrix() * OgreVector3Converter::toOgreVector(world_coordinate));
				}

			private:
				Core::ComponentInterfacePtr<ComponentInterfaces::IOgreCameraComponent> camera;
				OgreScreenSpaceCoordinatesCalculatorDesc desc;
		};

	} // namespace Graphics
} // namespace UnknownEngine
