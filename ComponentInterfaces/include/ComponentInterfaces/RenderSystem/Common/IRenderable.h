#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <AxisAlignedBoundingBox.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IRenderable : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType()
				{
					return "IRenderable";
				}

				virtual void setMaterialName(const char* material_name) = 0;
				
				virtual Math::AxisAlignedBoundingBox getAxisAlignedBoundingBox() = 0;
		};
	}
}
