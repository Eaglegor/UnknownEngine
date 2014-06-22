/*
 * Singleton.h
 *
 *  Created on: 22 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

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

#endif /* SINGLETON_H_ */
