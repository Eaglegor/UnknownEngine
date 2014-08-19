#pragma once

#include <ResourceManager_export.h>
#include <atomic>
#include <DataProvider/IDataProvider.h>
#include <ResourceContainer.h>

namespace UnknownEngine
{
	namespace Loader
	{

		/// Implementation of data provider with references counter
		class ReferencesCountingDataProvider : public IDataProvider
		{
			public:
				RESOURCEMANAGER_EXPORT
				ReferencesCountingDataProvider ( const std::string &name );

				/// Returns the loaded data
				RESOURCEMANAGER_EXPORT
				virtual const ResourceContainer& getResource() override;

				/// Increases references counter
				RESOURCEMANAGER_EXPORT
				virtual void reserve() override;
				
				/// Decreases references counter
				RESOURCEMANAGER_EXPORT
				virtual void release() override;

				/// Returns true if there are no references to this provider
				RESOURCEMANAGER_EXPORT
				virtual bool mayBeDestructed() const override;

			protected:

				virtual void internalLoad ( ResourceContainer &out_container ) = 0;

				ResourceContainer resource_container;

				/// Increases the references counter
				void increaseReferencesCounter();

				/// Decreases the references counter
				void decreaseReferencesCounter();

			private:
				bool loading_finished;
				volatile std::atomic<size_t> references_counter; ///< References counter

		};

	} // namespace Loader
} // namespace UnknownEngine
