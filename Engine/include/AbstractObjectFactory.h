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

		/**
		 * @brief Base class for object factories creating objects of single base type according to the passed descriptor
		 *
		 * \tparam ObjectType Base object type to create (e.g. \ref UnknownEngine::Core::Component "Component" )
		 * \tparam ObjectTypeId Object type identifier (e.g. \ref UnknownEngine::Core::ComponentType "ComponentType" )
		 * \tparam DescriptorClass Object descriptor type (e.g. \ref UnknownEngine::Core::ComponentDesc "ComponentDesc" )
		 */
		template <typename ObjectType, typename ObjectTypeId, typename DescriptorClass>
		class AbstractObjectFactory
		{
			public:
				AbstractObjectFactory() : internal_id ( INVALID_NUMERIC_IDENTIFIER ) {}

				virtual ~AbstractObjectFactory(){}
				
				/**
				 * @brief Compare to another factory based on internal id
				 * @param rhs - Second factory to compare with
				 * @return true if internal ids equal
				 */
				bool operator== ( const AbstractObjectFactory<ObjectType, ObjectTypeId, DescriptorClass> &rhs ) const
				{
					return internal_id == rhs.internal_id;
				}

				/**
				 * @brief Returns a factory name.
				 *
				 * The name must be unique across all registered factories.
				 *
				 * @return Factory name
				 */
				virtual const char* getName() = 0;

				/**
				 * @brief Returns a set of object type identifiers supported by this factory
				 * @return Set of identifiers of object types which can be created by this factory
				 */
				virtual const std::unordered_set<ObjectTypeId>& getSupportedTypes() = 0;

				/**
				 * @brief Checks if a factory is able to create specific type
				 * @param object_type - Type to check for
				 * @return true if the factory supports passed type
				 */
				virtual bool supportsType ( const ObjectTypeId &object_type ) = 0;

				/**
				 * @brief Creates an object according to passed descriptor
				 * @param desc - Object descriptor
				 * @return Pointer to a newly created object
				 */
				virtual ObjectType* createObject ( const DescriptorClass& desc ) = 0;

				/**
				 * @brief Deletes object considering it's creation process
				 * @param object - The object to be deleted
				 */
				virtual void destroyObject ( ObjectType* object ) = 0;

				/**
				  * @brief **Internal** method to get internal id when registering factory.
				  * \deprecated internal use only: **must not be used in user code**.
				  */
				UNKNOWNENGINE_INLINE
				NumericIdentifierType getInternalId()
				{
					return internal_id;
				}

				/**
				  * @brief **Internal** method to assign internal id when registering factory.
				  * \deprecated internal use only: **must not be used in user code**.
				  */
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
