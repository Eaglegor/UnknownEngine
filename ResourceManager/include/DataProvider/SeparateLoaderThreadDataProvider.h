#pragma once

#include <ResourceManager_export.h>
#include <memory>

#include <DataProvider/ReferencesCountingDataProvider.h>

namespace UnknownEngine
{
	namespace Loader
	{

		/// Data provider implementation loading resources in the separate thread
		class SeparateLoaderThreadDataProvider : public ReferencesCountingDataProvider
		{
			public:
				RESOURCEMANAGER_EXPORT
				SeparateLoaderThreadDataProvider ( const std::string &name );

				RESOURCEMANAGER_EXPORT
				virtual ~SeparateLoaderThreadDataProvider();

				/// Starts the loading thread
				RESOURCEMANAGER_EXPORT
				void startLoading() override;

			protected:
				virtual const ResourceContainer& internalGetResource() override;

			private:
				
				/// Worker method starter
				void separateLoaderThreadFunc();

		};

	} // namespace Loader
} // namespace UnknownEngine
