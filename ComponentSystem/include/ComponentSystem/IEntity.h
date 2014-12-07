#pragma once

#include <ComponentSystem_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
		struct ComponentDesc;

		class IEntity
		{
			public:
				COMPONENTSYSTEM_EXPORT
				virtual ~IEntity (){};

				COMPONENTSYSTEM_EXPORT
				virtual const char* getName() const = 0;

				COMPONENTSYSTEM_EXPORT
				virtual IComponent* createComponent(const ComponentDesc& desc) = 0;

				COMPONENTSYSTEM_EXPORT
				virtual void removeComponent ( IComponent *component ) = 0;
				
				COMPONENTSYSTEM_EXPORT
				virtual void removeAllComponents() = 0;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
