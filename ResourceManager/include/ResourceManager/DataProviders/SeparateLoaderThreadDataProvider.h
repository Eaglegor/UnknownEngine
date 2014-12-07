#pragma once

#include <ResourceManager_export.h>
#include <memory>

#include <ResourceManager/DataProviders/ReferencesCountingDataProvider.h>

namespace UnknownEngine
{
	namespace Core
	{

		class SeparateLoaderThreadDataProvider : public ReferencesCountingDataProvider
		{
			public:
				RESOURCEMANAGER_EXPORT
				SeparateLoaderThreadDataProvider ( const std::string &name );

				RESOURCEMANAGER_EXPORT
				virtual ~SeparateLoaderThreadDataProvider();

				RESOURCEMANAGER_EXPORT
				void startLoading() override;

			protected:
				RESOURCEMANAGER_EXPORT
				virtual const ResourceContainer& internalGetResource() override;

			private:
				void separateLoaderThreadFunc();

		};

	} // namespace Loader
} // namespace UnknownEngine
