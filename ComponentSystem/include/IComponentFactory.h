#pragma once
/*
 * ComponentFactory.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <unordered_set>
#include <string>
#include <vector>

#include <InlineSpecification.h>
#include <NumericIdentifierType.h>
#include <ComponentType.h>

namespace UnknownEngine
{
	namespace Core
	{

		class Properties;
		class Component;
		class MessageListenerDesc;
		class ComponentDesc;

		class IComponentFactory
		{
			public:

				bool operator==(const IComponentFactory& rhs){
					return getInternalId() == rhs.getInternalId();
				}

				virtual ~IComponentFactory ();
				virtual std::string getName () const = 0;
				virtual Component* createComponent ( const ComponentDesc &desc ) = 0;
				virtual bool canCreateComponentType ( const ComponentType &component_type_name ) const = 0;
				virtual const std::unordered_set<ComponentType>& getSupportedComponentTypeNames () const = 0;

			protected:
				IComponentFactory ():internal_id(INVALID_NUMERIC_IDENTIFIER){};

			private:
				friend class ComponentsManager;
				NumericIdentifierType internal_id;

				UNKNOWNENGINE_INLINE
				NumericIdentifierType getInternalId() const
				{
					return internal_id;
				}

				UNKNOWNENGINE_INLINE
				void setInternalId(NumericIdentifierType internal_id)
				{
					this->internal_id = internal_id;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
