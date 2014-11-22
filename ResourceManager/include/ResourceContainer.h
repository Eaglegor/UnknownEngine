/*
 * IDataProvider.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <string>
#include <boost/any.hpp>

namespace UnknownEngine
{
	namespace Loader
	{

		/**
		 * @brief Wrapper over the loaded resource data
		 */
		class ResourceContainer
		{
			public:
				/// Returns the data casted to specified type. Throws exception on bad cast.
				template<typename T>
				const T& getData() const
				{
					return boost::any_cast<const T&>(data);
				}

				/// Sets the data. Move version.
				template<typename T>
				void setData(T&& data)
				{
					this->data = std::move(data);
				}

				/// Sets the data. Copy version.
				template<typename T>
				void setData(const T& data)
				{
					this->data = data;
				}

			private:
				boost::any data; ///< Stored data

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
