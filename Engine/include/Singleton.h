/*
 * Singleton.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <assert.h>
#include <Exception.h>
#include <memory>

namespace UnknownEngine
{
	namespace Core
	{

		/// Base for singleton classes
		template<typename T, typename... CtorArgs>
		class Singleton
		{
			public:
				static T* createInstance(CtorArgs&&... args)
				{
					if (instance) return instance;
					instance = new T(std::forward<CtorArgs>(args)...);
					return instance;
				}

				/**
				 * @brief get singleton instance
				 * @return pointer to the instance
				 */
				static T* getSingleton()
				{
					return instance;
				}

				static void destroyInstance()
				{
					delete instance;
					instance = nullptr;
				}

			protected:
				Singleton(){}

				virtual ~Singleton(){}

				explicit Singleton ( const Singleton& rhs );

				static T* instance;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
