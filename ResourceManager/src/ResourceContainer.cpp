/*
 * IDataProvider.cpp
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <ResourceContainer.h>
 
namespace UnknownEngine
{
  namespace Loader
  {

    template<typename T>
    void ResourceContainer::setData(T &&data)
    {
      this->data = std::move<T>(data);
    }

    template<typename T>
    void ResourceContainer::setData(const T &data)
    {
      this->data = data;
    }

    template<typename T>
    const T &ResourceContainer::getData() const
    {
      return boost::any_cast<T>(data);
    }

  } /* namespace Core */
} /* namespace UnknownEngine */
