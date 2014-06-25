#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		class SystemPartId
		{
			public:

				enum Type
				{
					SUBSYSTEM,
					COMPONENT
				};

				explicit SystemPartId(const std::string &sender_name) :
					sender_name(sender_name)
				{
				}

				bool operator==(const SystemPartId& rhs)
				{
					return sender_name == rhs.sender_name;
				}

			private:
				std::string sender_name;
				std::string component_name;
				std::string entity_name;
				std::string subsystem_name;
		};
	}
}
