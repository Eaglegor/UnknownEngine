#include <Components/OgreScreenSpacePositionCalculator.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		OgreScreenSpacePositionCalculator::OgreScreenSpacePositionCalculator ( const char* name, const OgreScreenSpaceCoordinatesCalculatorDesc& desc ):
		Core::BaseComponent(name),
		camera(desc.camera)
		{
		}

		
		Math::Vector3 OgreScreenSpacePositionCalculator::getScreenSpaceCoordinate ( const Math::Vector3& world_coordinate )
		{
			return OgreVector3Converter::fromOgreVector(camera->getOgreCamera()->getProjectionMatrix() * camera->getOgreCamera()->getViewMatrix() * OgreVector3Converter::toOgreVector(world_coordinate));
		}
		
		Core::IComponentInterface* OgreScreenSpacePositionCalculator::getInterface ( const Core::ComponentType& type )
		{
			if(type == ComponentInterfaces::IScreenSpaceCoordinatesCalculator::getType()){
				return static_cast<ComponentInterfaces::IScreenSpaceCoordinatesCalculator*>(this);
			}
			return nullptr;
		}
	}
}