#pragma once
/*
 * ComponentFactory.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <unordered_set>
#include <string>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{

		template <typename T>
		class Properties;

		class Component;
		class ComponentType;

		class IComponentFactory
		{
			public:

				bool operator==(const IComponentFactory& rhs){
					return getInternalId() == rhs.getInternalId();
				}

				virtual ~IComponentFactory ();
				virtual std::string getName () const = 0;
				virtual Component* createComponent ( const ComponentType &component_type, const Properties<std::string> &properties ) = 0;
				virtual bool canCreateComponentType ( const ComponentType &component_type_name ) const = 0;
				virtual const std::unordered_set<ComponentType>& getSupportedComponentTypeNames () const = 0;

			protected:
				IComponentFactory ():internal_id(-1){};

			private:
				friend class ComponentManager;
				int internal_id;

				UNKNOWNENGINE_INLINE
				int getInternalId() const
				{
					return internal_id;
				}

				UNKNOWNENGINE_INLINE
				void setInternalId(int internal_id)
				{
					this->internal_id = internal_id;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
