#pragma once

#include <MessageSystem/IMessageListener.h>
#include <ExportedMessages/StopEngineActionMessage.h>
#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		class MainLoopComponent;

		class StopEngineListener : public IMessageListener
		{
			public:
				StopEngineListener ( const std::string name, MainLoopComponent* main_loop );
				virtual void processMessage ( const PackedMessage &msg ) override;
				virtual const char* getName() const;

			private:
				std::string name;
				MainLoopComponent* main_loop;
		};
	}
}
