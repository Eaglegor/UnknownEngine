#pragma once

#include <unordered_set>
#include <NumericIdentifierType.h>
#include <InlineSpecification.h>
#include <Exception.h>
#include <Properties/Properties_fwd.h>

namespace UnknownEngine
{
	namespace Core
	{

		template <typename ObjectType, typename ObjectTypeId, typename DescriptorClass>
		class AbstractObjectFactory
		{
			public:
				AbstractObjectFactory() : internal_id ( INVALID_NUMERIC_IDENTIFIER ) {}

				virtual ~AbstractObjectFactory(){}

				bool operator== ( const AbstractObjectFactory<ObjectType, ObjectTypeId, DescriptorClass> &rhs ) const
				{
					return internal_id == rhs.internal_id;
				}

				virtual const char* getName() const = 0;

				virtual bool supportsType ( const ObjectTypeId &object_type ) const = 0;

				virtual ObjectType* createObject ( const DescriptorClass& desc ) = 0;

				virtual void destroyObject ( ObjectType* object ) = 0;

				UNKNOWNENGINE_INLINE
				NumericIdentifierType getInternalId() const
				{
					return internal_id;
				}

				UNKNOWNENGINE_INLINE
				void setInternalId ( const NumericIdentifierType &internal_id )
				{
					this->internal_id = internal_id;
				}

			private:
				NumericIdentifierType internal_id;

		};

	} // namespace Core
} // namespace UnknownEngine
