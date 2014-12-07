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
				AbstractObjectFactory() {}

				virtual ~AbstractObjectFactory(){}

				virtual const char* getName() const = 0;

				virtual bool supportsType ( const ObjectTypeId &object_type ) const = 0;

				virtual ObjectType* createObject ( const DescriptorClass& desc ) = 0;

				virtual void destroyObject ( ObjectType* object ) = 0;
				
				virtual void setInternalId(int a){};
				virtual int getInternalId(){return 0;};
		};

	} // namespace Core
} // namespace UnknownEngine
