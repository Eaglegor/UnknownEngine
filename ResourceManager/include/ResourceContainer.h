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

    class ResourceContainer
    {
      public:
	template<typename T>
	const T& getData() const;

	template<typename T>
	void setData(T&& data);

	template<typename T>
	void setData(const T& data);

      private:
	boost::any data;

    };

  } /* namespace Core */
} /* namespace UnknownEngine */
