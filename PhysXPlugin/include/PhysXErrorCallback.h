#pragma once

#include <foundation/PxErrorCallback.h>

namespace UnknownEngine
{
	
	namespace Core
	{
		class EngineContext;
		class LogHelper;
	}

	namespace Physics
	{
		class PhysXErrorCallback : public physx::PxErrorCallback
		{
		public:
			
			PhysXErrorCallback(Core::LogHelper &logger);
			
			virtual void reportError ( physx::PxErrorCode::Enum code, const char* message, const char* file, int line );
			
		private:
			Core::LogHelper &logger;
		};
	}
}