#pragma once
#include <DataProvider/ReferencesCountingDataProvider.h>

namespace UnknownEngine
{
	namespace Loader
	{
		class LazyLoadDataProvider : public Loader::ReferencesCountingDataProvider
		{
		public:
			LazyLoadDataProvider ( const std::string& name );
			virtual ~LazyLoadDataProvider();
			
			/// Does nothing. All loading is done in getResource()
			virtual void startLoading(){};
			
		protected:
			virtual const ResourceContainer& internalGetResource();
			
		};
	}
}