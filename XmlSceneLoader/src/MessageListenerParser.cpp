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

		Core::ReceivedMessageDescriptorsList MessageListenerParser::parseMessageListener(const ptree &event_listener_node, const ConstantsHolder *constants_holder)
		{
			Core::ReceivedMessageDescriptorsList messages;
			for(const ptree::value_type &iter : event_listener_node)
			{
				if(iter.first == Tags::MESSAGE){
					messages.push_back(parseMessageDesc(iter.second, constants_holder));
				}
			}
			return std::move(messages);
		}

		Core::ReceivedMessageDesc MessageListenerParser::parseMessageDesc(const ptree &message_node, const ConstantsHolder *constants_holder)
		{
			Core::ReceivedMessageDesc message_desc;

			boost::optional<const ptree&> receive_policy = message_node.get_child_optional( Tags::RECEIVE_POLICY);
			if(receive_policy.is_initialized())
			{
				message_desc.receive_policy_type_name = receive_policy.get().get_child(XMLATTR).get<std::string>(Attributes::RECEIVE_POLICY::TYPE);
				boost::optional<const ptree&> receive_policy_options = receive_policy.get().get_child_optional(Tags::OPTIONS_SECTION);
				if(receive_policy_options.is_initialized())
				{
					message_desc.receive_policy_options = OptionsParser::parseOptions(receive_policy_options.get(), constants_holder);
				}
			}

			return message_desc;
		}

	} // namespace Core
} // namespace UnknownEngine
