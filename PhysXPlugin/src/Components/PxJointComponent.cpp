#include <stdafx.h>
#include <Components/PxJointComponent.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Physics
	{

		PxJointComponent::PxJointComponent(const std::string& name, PhysXSubsystem* physics_subsystem, Core::EngineContext* engine_context) :
			Core::BaseComponent ( name.c_str() ),
			physics_subsystem ( physics_subsystem ),
			actor1(nullptr),
			actor2(nullptr),
			engine_context(engine_context),
			logger(name)
		{
		}

		PxJointComponent::~PxJointComponent()
		{
		}

		void PxJointComponent::initializeLogger(Core::LogSeverity severity)
		{
			logger.init(severity);
		}

	}
}
