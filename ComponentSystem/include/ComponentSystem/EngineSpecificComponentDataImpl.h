#pragma once

#include <ComponentSystem/EngineSpecificComponentData.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineSpecificComponentDataImpl : public EngineSpecificComponentData
		{
			private:
				friend class ComponentsManager;
				
				size_t ref_counter;
				std::string factory_name;
		};
	}
}