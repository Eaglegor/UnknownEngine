#pragma once
#include <ComponentSystem_export.h>
#include <ComponentSystem/ComponentType.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct ComponentDesc;
		class IComponent;
		
		class IComponentFactory
		{
			public:
				COMPONENTSYSTEM_EXPORT
				virtual ~IComponentFactory(){}

				COMPONENTSYSTEM_EXPORT
				virtual const char* getName() const = 0;

				COMPONENTSYSTEM_EXPORT
				virtual bool supportsType ( const ComponentType &object_type ) const = 0;

				COMPONENTSYSTEM_EXPORT
				virtual IComponent* createObject ( const ComponentDesc& desc ) = 0;

				COMPONENTSYSTEM_EXPORT
				virtual void destroyObject ( IComponent* object ) = 0;
		};

	} // namespace Core
} // namespace UnknownEngine
