#pragma once

#include <unordered_set>
#include <NumericIdentifierType.h>
#include <InlineSpecification.h>
#include <Exception.h>

namespace UnknownEngine {
	namespace Core {

		class Properties;
		UNKNOWNENGINE_SIMPLE_EXCEPTION(NoSuitableFactoryFound);

		template <typename ObjectType, typename ObjectTypeId, typename DescriptorClass>
		class AbstractObjectFactory
		{
			public:
				AbstractObjectFactory():internal_id(INVALID_NUMERIC_IDENTIFIER){}

				bool operator==(const AbstractObjectFactory<ObjectType, ObjectTypeId, DescriptorClass> &rhs) const
				{
					return internal_id == rhs.internal_id;
				}

				virtual const std::string getName() = 0;

				virtual const std::unordered_set<ObjectTypeId>& getSupportedTypes() = 0;
				virtual const bool supportsType(const ObjectTypeId &object_type) = 0;

				virtual ObjectType* createObject(const DescriptorClass& desc) = 0;
				virtual void disposeObject(ObjectType* object) = 0;

				UNKNOWNENGINE_INLINE
				NumericIdentifierType getInternalId()
				{
					return internal_id;
				}

				UNKNOWNENGINE_INLINE
				void setInternalId(const NumericIdentifierType &internal_id)
				{
					this->internal_id = internal_id;
				}

			private:
				NumericIdentifierType internal_id;

		};

	} // namespace Core
} // namespace UnknownEngine
