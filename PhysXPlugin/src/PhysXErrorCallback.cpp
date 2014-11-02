#include <PhysXErrorCallback.h>

#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		PhysXErrorCallback::PhysXErrorCallback(Utils::LogHelper* log_helper):
		log_helper(log_helper)
		{}
		
		void PhysXErrorCallback::reportError ( physx::PxErrorCode::Enum code, const char* message, const char* file, int line )
		{
			LOG_ERROR(log_helper, "PhysX SDK error: " + std::string(message) + ". File: " + std::string(file) + " (line " + std::to_string(line) + ")" );
		}
		
	}
}