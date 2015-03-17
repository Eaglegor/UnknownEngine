#pragma once
#include <ComponentSystem/IComponentInterface.h>
#include <functional>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IContextualActionsMapper : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){ return "IContextualActionsMapper"; }
			
			virtual void addSimpleAction(const char* context_name, const char* action_slot_name, std::function<void()> action_callback) = 0;
			virtual void addRangedAction(const char* context_name, const char* action_slot_name, std::function<void(Math::Scalar)> action_callback) = 0;
			
			virtual void removeSimpleAction(const char* context_name, const char* action_slot_name) = 0;
			virtual void removeRangedAction(const char* context_name, const char* action_slot_name) = 0;
		};
	}
}