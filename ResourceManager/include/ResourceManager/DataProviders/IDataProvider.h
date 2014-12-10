#pragma once

#include <ResourceManager_export.h>
#include <ResourceManager/DataProviders/DataProviderType.h>

namespace UnknownEngine
{

	namespace Core
	{

        class ResourceContainer;

		class IDataProvider
		{
			public:
				RESOURCEMANAGER_EXPORT
				virtual ~IDataProvider()
				{}

				RESOURCEMANAGER_EXPORT
                virtual void startLoading() = 0;

				RESOURCEMANAGER_EXPORT
                virtual const ResourceContainer& getResource() = 0;

				RESOURCEMANAGER_EXPORT
				virtual const DataProviderType getType() const = 0;

				RESOURCEMANAGER_EXPORT
				virtual const char* getName() const = 0;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
