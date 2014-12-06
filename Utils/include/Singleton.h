#pragma once

#include <assert.h>
#include <Exception.h>
#include <memory>

namespace UnknownEngine
{
	namespace Core
	{

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
