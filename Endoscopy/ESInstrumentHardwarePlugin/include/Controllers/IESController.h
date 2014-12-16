#pragma once

#include <Controllers/ESControllerType.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class IESController
		{
		public:
			virtual ~IESController(){};
			
			virtual void init() = 0;
			virtual void shutdown() = 0;
			virtual ESControllerType getType() = 0;
			virtual const char* getName() = 0;
		};
	}
}