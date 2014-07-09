/*
 * Singleton.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <assert.h>

namespace UnknownEngine
{
	namespace Core
	{

		/// Base for singleton classes
		template<typename T>
		class Singleton
		{
			public:
				virtual ~Singleton()
				{
					instance = nullptr;
				}

				/**
				 * @brief get singleton instance
				 * @return pointer to the instance
				 */
				static T* getSingleton()
				{
					assert(instance != nullptr);
					return instance;
				}

				/**
				 * @brief sets singleton instance to a specified value. Old instance isn't deleted.
				 * @param new_instance - a new instance to set to a singleton
				 */
				static void initSingletonInstance(T* new_instance)
				{
					if (instance == nullptr)
					{
						instance = new_instance;
					}
				}

			protected:
				Singleton()
				{
					assert(instance == nullptr);
					instance = static_cast<T*>(this);
				}

				explicit Singleton(const Singleton& rhs);

				static T* instance;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
