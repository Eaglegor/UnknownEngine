#pragma once

#include <Exception.h>

namespace UnknownEngine
{
  namespace Core
  {
	/// Is thrown if no factory suitable for object creation is found
    UNKNOWNENGINE_SIMPLE_EXCEPTION(NoSuitableFactoryFoundException);
  }
}
