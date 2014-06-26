#include <stdafx.h>

#include <MessageListenerParser.h>
#include <SupportedTags.h>
#include <OptionsParser.h>
#include <ConstantsHolder.h>

namespace UnknownEngine {
	namespace Loader {

		using namespace boost::property_tree;

		MessageListenerParser::MessageListenerParser()
		{
		}

		Core::MessageListenerDesc MessageListenerParser::parseMessageListener(const ptree &event_listener_node, const ConstantsHolder *constants_holder)
		{
			Core::MessageListenerDesc listener_desc;
			listener_desc.name = event_listener_node.get_child(XMLATTR).get<std::string>(Attributes::MESSAGE_LISTENER::NAME);
			for(const ptree::value_type &iter : event_listener_node)
			{
				if(iter.first == Tags::MESSAGE){
					listener_desc.events.push_back(parseMessageDesc(iter.second, constants_holder));
				}
			}
			return listener_desc;
		}

		Core::MessageListenerDesc::MessageDesc MessageListenerParser::parseMessageDesc(const ptree &message_node, const ConstantsHolder *constants_holder)
		{
			Core::MessageListenerDesc::MessageDesc message_desc;

			boost::optional<const ptree&> receive_policy = message_node.get_child_optional("receive_policy");
			if(receive_policy.is_initialized())
			{
				message_desc.receive_policy_type_name = receive_policy.get().get_child(XMLATTR).get<std::string>(Attributes::RECEIVE_POLICY::TYPE);
				boost::optional<const ptree&> receive_policy_options = receive_policy.get().get_child_optional("options_section");
				if(receive_policy_options.is_initialized())
				{
					message_desc.receive_policy_options = OptionsParser::parseOptions(receive_policy_options.get(), constants_holder);
				}
			}

			return message_desc;
		}

	} // namespace Core
} // namespace UnknownEngine
