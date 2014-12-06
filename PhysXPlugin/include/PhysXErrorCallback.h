#pragma once

#include <foundation/PxErrorCallback.h>

namespace UnknownEngine
{
	
	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Physics
	{
		class PhysXErrorCallback : public physx::PxErrorCallback
		{
		public:
			
			PhysXErrorCallback(Core::ILogger* logger);
			
			virtual void reportError ( physx::PxErrorCode::Enum code, const char* message, const char* file, int line );
			
		private:
			Core::ILogger* logger;
		};
	}
}