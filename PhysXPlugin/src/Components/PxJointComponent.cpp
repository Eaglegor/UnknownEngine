#include <Components/PxJointComponent.h>

namespace UnknownEngine
{
	namespace Physics
	{

		PxJointComponent::PxJointComponent(const std::string& name, PhysXSubsystem* physics_subsystem, Core::EngineContext* engine_context) :
			Core::BaseComponent ( name ),
			physics_subsystem ( physics_subsystem ),
			actor1(nullptr),
			actor2(nullptr),
			engine_context(engine_context)
		{
		}

		PxJointComponent::~PxJointComponent()
		{
		}

		void PxJointComponent::initializeLogger(Core::LogMessage::Severity severity)
		{
			log_helper.reset(new Core::LogHelper(getName(), severity, engine_context));
		}

	}
}
