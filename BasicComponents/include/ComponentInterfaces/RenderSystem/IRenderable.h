#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IRenderable : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getTypeName()
				{
					return "IRenderable";
				}

				virtual void setMaterialName(const char* material_name) = 0;
		};
	}
}