#pragma once

#include <unordered_set>
#include <NumericIdentifierType.h>
#include <InlineSpecification.h>
#include <Exception.h>
#include <NoSuitableFactoryFoundException.h>

namespace UnknownEngine {
	namespace Core {

		class Properties;

		/// Base class for object factories creating objects of single base type according to the passed descriptor
		template <typename ObjectType, typename ObjectTypeId, typename DescriptorClass>
		class AbstractObjectFactory
		{
			public:
				AbstractObjectFactory():internal_id(INVALID_NUMERIC_IDENTIFIER){}

				/**
				 * @brief Compare factories considering internal numeric ids assigned when registering factories
				 * @param rhs - second factory to compare with
				 * @return true if internal ids equal
				 */
				bool operator==(const AbstractObjectFactory<ObjectType, ObjectTypeId, DescriptorClass> &rhs) const
				{
					return internal_id == rhs.internal_id;
				}

				/**
				 * @brief Get a factory name. Must be unique across all registered factories.
				 * @return name of factory
				 */
				virtual const std::string getName() = 0;

				/**
				 * @brief Get a set of object type identifiers supported by this factory
				 * @return set of object types which can be created by this factory
				 */
				virtual const std::unordered_set<ObjectTypeId>& getSupportedTypes() = 0;

				/**
				 * @brief Check if a factory is able to create specific type
				 * @param object_type A type to check
				 * @return true if the factory supports passed type
				 */
				virtual const bool supportsType(const ObjectTypeId &object_type) = 0;

				/**
				 * @brief Creates an object
				 * @param desc Object's descriptor
				 * @return Pointer to a newly created object
				 */
				virtual ObjectType* createObject(const DescriptorClass& desc) = 0;

				/**
				 * @brief Deletes object considering it's creation process
				 * @param object The object to be deleted
				 */
				virtual void disposeObject(ObjectType* object) = 0;

				/**
				  * @brief internal method to get internal id when registering factories. Must not be used in user code.
				  */
				UNKNOWNENGINE_INLINE
				NumericIdentifierType getInternalId()
				{
					return internal_id;
				}

				/**
				  * @brief internal method to assign internal id when registering factories. Must not be used in user code.
				  */
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
