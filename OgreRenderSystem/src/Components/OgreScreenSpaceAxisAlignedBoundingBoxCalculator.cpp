#include <Components/OgreScreenSpaceAxisAlignedBoundingBoxCalculator.h>
#include <ComponentInterfaces/RenderSystem/Common/IRenderable.h>
#include <AxisAlignedBoundingBox.h>
#include <Utils/Vector3Utils.h>

namespace UnknownEngine
{
    namespace Graphics
    {
        OgreScreenSpaceAxisAlignedBoundingBoxCalculator::OgreScreenSpaceAxisAlignedBoundingBoxCalculator(const char* name, OgreScreenSpaceAxisAlignedBoundingBoxCalculatorDesc &desc):
        Core::BaseComponent(name),
        screen_space_coordinates_calculator(desc.screen_space_coordinates_calculator)
        {
        }

        Math::AxisAlignedBoundingBox OgreScreenSpaceAxisAlignedBoundingBoxCalculator::calculateScreenSpaceAxisAlignedBoundingBox(ComponentInterfaces::IRenderable *renderable)
        {
            Math::AxisAlignedBoundingBox three_d_box = renderable->getAxisAlignedBoundingBox();
			
			Math::AxisAlignedBoundingBox ss_box;
			ss_box.min = screen_space_coordinates_calculator->getScreenSpaceCoordinate(three_d_box.min);
			ss_box.max = screen_space_coordinates_calculator->getScreenSpaceCoordinate(three_d_box.max);
			
			Math::Vector3 points[6];
			
			points[0].setX(three_d_box.min.x());
			points[0].setY(three_d_box.min.y());
			points[0].setZ(three_d_box.max.z());
			
			points[1].setX(three_d_box.min.x());
			points[1].setY(three_d_box.max.y());
			points[1].setZ(three_d_box.min.z());
			
			points[2].setX(three_d_box.max.x());
			points[2].setY(three_d_box.min.y());
			points[2].setZ(three_d_box.min.z());

			points[3].setX(three_d_box.max.x());
			points[3].setY(three_d_box.max.y());
			points[3].setZ(three_d_box.min.z());
			
			points[4].setX(three_d_box.max.x());
			points[4].setY(three_d_box.min.y());
			points[4].setZ(three_d_box.max.z());
			
			points[5].setX(three_d_box.min.x());
			points[5].setY(three_d_box.max.y());
			points[5].setZ(three_d_box.max.z());
			
			for(int i = 0; i < 6; ++i)
			{
				Math::Vector3 ss_point_coordinate = screen_space_coordinates_calculator->getScreenSpaceCoordinate(points[i]);
				Math::Vector3Utils::selectMaxComponentValues(ss_box.max, ss_point_coordinate, ss_box.max);
				Math::Vector3Utils::selectMinComponentValues(ss_box.min, ss_point_coordinate, ss_box.min);
			}
			
			return ss_box;
        }

        Core::IComponentInterface* OgreScreenSpaceAxisAlignedBoundingBoxCalculator::getInterface(const Core::ComponentType &type)
        {
            if(type == ComponentInterfaces::IScreenSpaceAxisAlignedBoundingBoxCalculator::getType()) {
                return static_cast<ComponentInterfaces::IScreenSpaceAxisAlignedBoundingBoxCalculator*>(this);
            }
            return nullptr;
        }

        bool OgreScreenSpaceAxisAlignedBoundingBoxCalculator::init() 
        {
			if(!screen_space_coordinates_calculator) return false;
			return true;
        }

        void OgreScreenSpaceAxisAlignedBoundingBoxCalculator::shutdown()
        {

        }

    }
}

