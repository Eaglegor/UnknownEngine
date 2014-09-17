#pragma once

#include <functional>

namespace UnknownEngine
{
	namespace IO
	{

		enum class ActionType
		{
			SINGLE_ACTION, // Performs only on state change
			CONTINUOUS_ACTION // Performs on every frame if some input is active
		};
		
		struct ActionPerformerDescriptor
		{
			std::string context_name;
			std::string action_name;
			ActionType type;
			
			virtual ~ActionPerformerDescriptor(){};
		};
		
		struct SimpleActionPerformerDescriptor : public ActionPerformerDescriptor
		{
			std::function<void()> callback;
		};
		
		struct RangedActionPerformerDescriptor : public ActionPerformerDescriptor
		{
			std::function<void(const Math::Scalar&)> callback;
		};
		
	}
}