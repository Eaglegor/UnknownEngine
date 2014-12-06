#pragma once

#include <ComponentSystem_export.h>
#include <ComponentType.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{

		class Entity;

		class IComponent
		{
			public:

				virtual void init ( const Entity* parent_entity ) = 0;

				virtual void shutdown() = 0;

				virtual ComponentType getType() const = 0;

				virtual const char* getName() const = 0;

				virtual ~IComponent () {};

		};

	} /* namespace Core */
	
} /* namespace UnknownEngine */
