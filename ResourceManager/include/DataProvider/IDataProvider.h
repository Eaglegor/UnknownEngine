#pragma once

#include <string>
#include <DataProvider/DataProviderType.h>
#include <InlineSpecification.h>
#include <Properties/Properties_fwd.h>

namespace UnknownEngine
{

	namespace Loader
	{

        class ResourceContainer;

		class IDataProvider
		{
			public:
				virtual ~IDataProvider()
				{
				}

				explicit IDataProvider(const std::string &name):
					name(name){}

                virtual void startLoading() = 0;

                virtual const ResourceContainer& getResource() = 0;

                virtual void reserve() = 0;

                virtual void release() = 0;

                virtual bool mayBeDestructed() const = 0;

				virtual const DataProviderType getType() const = 0;

				UNKNOWNENGINE_INLINE
				std::string getName() const
				{
					return name;
				}

			private:
				std::string name;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
