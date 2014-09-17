#pragma once

#include <unordered_map>

#include <Keys.h>
#include <KeycodeHash.h>
#include <Actions/SimpleAction.h>
#include <Actions/RangedAction.h>
#include <EventHandlers/KeyboardEventHandler.h>
#include <Actions/ActionPerformerDescriptor.h>

namespace UnknownEngine
{
	namespace IO
	{
		class InputContext
		{
		public:
			InputContext(bool enabled = false);
			
			enum class EventInterceptionStatus
			{
				INTERCEPTED,
				NOT_INTERCEPTED
			};
			
			EventInterceptionStatus processEvent(Key &key, KeyState &state);

			void addSimpleActionPerformer( const UnknownEngine::IO::SimpleActionPerformerDescriptor& desc );
			void performActions();
			
			bool isEnabled() const;
			void setEnabled(bool new_enabled);
			
		private:
			bool enabled;
			std::unordered_map<Key, KeyboardEventHandler> keyboard_events;
		};
	}
}