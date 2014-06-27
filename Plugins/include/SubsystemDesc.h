#ifndef SUBSYSTEMDESC_H
#define SUBSYSTEMDESC_H

#include <vector>
#include <MessageSystem/MessageListenerDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct SubsystemDesc
		{
			std::string name;
			std::string module_name;
			std::vector<MessageListenerDesc> message_listeners;
			Properties creation_options;
		};
	}
}

#endif // SUBSYSTEMDESC_H