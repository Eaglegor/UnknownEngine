#include <stdafx.h>
#include <PhysXErrorCallback.h>

#include <Logging.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		PhysXErrorCallback::PhysXErrorCallback(Core::ILogger* logger):
		logger(logger)
		{}
		
		void PhysXErrorCallback::reportError ( physx::PxErrorCode::Enum code, const char* message, const char* file, int line )
		{
			LOG_ERROR(logger, "PhysX SDK error: " + std::string(message) + ". File: " + std::string(file) + " (line " + std::to_string(line) + ")" );
		}
		
	}
}