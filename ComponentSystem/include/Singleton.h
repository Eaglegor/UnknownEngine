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

		template<typename T>
		class Singleton
		{
			public:
				virtual ~Singleton()
				{
					instance = nullptr;
				}

				static T* getSingleton()
				{
					assert(instance != nullptr);
					return instance;
				}

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
