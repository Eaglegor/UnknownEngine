#pragma once

#include <MessageSystem/IMessageListener.h>
#include <ExportedMessages/StopEngineActionMessage.h>
#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		class MainLoop;

		class StopEngineListener : public IMessageListener
		{
			public:
				StopEngineListener ( const std::string name, MainLoop* main_loop );
				virtual void processMessage ( const PackedMessage &msg ) override;

			private:
				MainLoop* main_loop;
		};
	}
}
