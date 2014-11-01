#pragma once

#include <foundation/PxErrorCallback.h>

namespace UnknownEngine
{
	
	namespace Core
	{
		class EngineContext;
	}
	
	namespace Utils
	{
		class LogHelper;
	}
	
	namespace Physics
	{
		class PhysXErrorCallback : public physx::PxErrorCallback
		{
		public:
			
			PhysXErrorCallback(Utils::LogHelper* log_helper);
			
			virtual void reportError ( physx::PxErrorCode::Enum code, const char* message, const char* file, int line );
			
		private:
			Utils::LogHelper* log_helper;
		};
	}
}