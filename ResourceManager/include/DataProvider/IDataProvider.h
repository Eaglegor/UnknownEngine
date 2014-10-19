/*
 * IDataProvider.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

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

		/**
		 * @brief The loader and holder of single resource instance
		 *
		 * ###Concept
		 * All stuff in the simulation (sounds, textures, models, texts) are called resources.
		 * To simplify the loading/unloading and reuse of resources we may use the resource manager.
		 * Resource manager doesn't know, how to load anything. It uses the loaders provided by
		 * plugins. Such loaders are called data providers. The single data provider is responsible
		 * for loading the single resource and storing it at least until it's not needed anymore.
		 *
		 * ###Usage
		 * When you want to load some resource you create the data provider. Then you call the startLoading()
		 * method to indicate that you're ready to load. After that you can get the data loaded by the
		 * call to getResource() method. When you are finished using data you must call release() method to
		 * indicate this fact. It will help the resource manager to manage memory destroying the resources
		 * that are not needed anymore.
		 *
		 * To create data providers one needs to use the factories accessible from the resource manager.
		 *
		 */

		class IDataProvider
		{
			public:
				virtual ~IDataProvider()
				{
				}

				explicit IDataProvider(const std::string &name):
					name(name){}

				/**
				 * @brief Starts loading resource. May cause creation of separate thread.
				 */
                virtual void startLoading() = 0;

				/**
				 * @brief Gets the loaded data
				 * @return Container holding loaded data
				 */
                virtual const ResourceContainer& getResource() = 0;

				/**
				 * @brief Informs data provider that the user wants to get data
				 */
                virtual void reserve() = 0;
				
				/**
				 * @brief Informs data provider that the user doesn't need it's data anymore
				 */
                virtual void release() = 0;

				/**
				 * @brief Indicates if data provider may be destroyed. Is called by resource manager.
				 * @return true if resource manager is allowed to delete this provider
				 */
                virtual bool mayBeDestructed() const = 0;

				/**
				 * @brief Returns the type of this data provider
				 * @return Data provider type
				 */
				virtual const DataProviderType getType() = 0;

				UNKNOWNENGINE_INLINE
				std::string getName()
				{
					return name;
				}

			private:
				std::string name;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
