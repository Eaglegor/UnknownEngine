/*
 * IDataProvider.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <string>

namespace UnknownEngine
{

    namespace Core
    {
        class Properties;
    }

	namespace Loader
	{

        class ResourceContainer;

		class IDataProvider
		{
			public:
				virtual ~IDataProvider()
				{
				}

                virtual void startLoading() = 0;
                virtual const ResourceContainer& getResource() const = 0;
                virtual void release() = 0;
                virtual bool mayBeDestructed() const = 0;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
