#include <stdafx.h>

#include <MessageListenerParser.h>
#include <SupportedTags.h>
#include <OptionsParser.h>
#include <ConstantsHolder.h>
#include <MessageSystem/MessageListenerRules.h>
#include <MessageSystem/MessageSenderRules.h>

namespace UnknownEngine
{
	namespace Loader
	{

		using namespace boost::property_tree;

		MessageListenerParser::MessageListenerParser()
		{
		}

		MessageListenerParser::MessagingRules MessageListenerParser::parseMessagingRules ( const ptree& event_listener_node, const ConstantsHolder* constants_holder )
		{
			MessagingRules rules;
			for ( const ptree::value_type & iter : event_listener_node )
			{
				if ( iter.first == Tags::LISTENER_RULES )
				{
					rules.listener_rules = parseListenerRules(iter.second, constants_holder);
				}
				if ( iter.first == Tags::SENDER_RULES )
				{
					rules.sender_rules = parseSenderRules(iter.second, constants_holder);
				}
			}
			return std::move(rules);
		}
		
		Core::MessageListenerRules MessageListenerParser::parseListenerRules ( const ptree &event_listener_node, const ConstantsHolder *constants_holder )
		{
			Core::MessageListenerRules messages;
			for ( const ptree::value_type & iter : event_listener_node )
			{
				if ( iter.first == Tags::MESSAGE )
				{
					messages.push_back ( parseListenerRule ( iter.second, constants_holder ) );
				}
			}
			return std::move ( messages );
		}
		
		Core::MessageSenderRules MessageListenerParser::parseSenderRules ( const ptree &event_listener_node, const ConstantsHolder *constants_holder )
		{
			Core::MessageSenderRules messages;
			for ( const ptree::value_type & iter : event_listener_node )
			{
				if ( iter.first == Tags::MESSAGE )
				{
					messages.push_back ( parseSenderRule ( iter.second, constants_holder ) );
				}
			}
			return std::move ( messages );
		}

		Core::MessageListenerRule MessageListenerParser::parseListenerRule ( const ptree &message_node, const ConstantsHolder *constants_holder )
		{
			Core::MessageListenerRule message_desc;
			message_desc.message_type_name = message_node.get_child ( XMLATTR ).get<std::string> ( Attributes::MESSAGE::TYPE );
			boost::optional<const ptree&> receive_policy = message_node.get_child_optional ( Tags::RECEIVE_POLICY );
			if ( receive_policy.is_initialized() )
			{
				message_desc.receive_policy_type_name = receive_policy.get().get_child ( XMLATTR ).get<std::string> ( Attributes::RECEIVE_POLICY::TYPE );
				boost::optional<const ptree&> receive_policy_options = receive_policy.get().get_child_optional ( Tags::OPTIONS_SECTION );
				if ( receive_policy_options.is_initialized() )
				{
					message_desc.receive_policy_options = OptionsParser::parseOptions ( receive_policy_options.get(), constants_holder );
				}
			}
			return message_desc;
		}
		
		Core::MessageSenderRule MessageListenerParser::parseSenderRule ( const ptree &message_node, const ConstantsHolder *constants_holder )
		{
			Core::MessageSenderRule message_desc;
			message_desc.message_type_name = message_node.get_child ( XMLATTR ).get<std::string> ( Attributes::MESSAGE::TYPE );
			boost::optional<const ptree&> receive_policy = message_node.get_child_optional ( Tags::DELIVERY_POLICY );
			if ( receive_policy.is_initialized() )
			{
				message_desc.delivery_policy_type_name = receive_policy.get().get_child ( XMLATTR ).get<std::string> ( Attributes::RECEIVE_POLICY::TYPE );
				boost::optional<const ptree&> receive_policy_options = receive_policy.get().get_child_optional ( Tags::OPTIONS_SECTION );
				if ( receive_policy_options.is_initialized() )
				{
					message_desc.delivery_policy_options = OptionsParser::parseOptions ( receive_policy_options.get(), constants_holder );
				}
			}
			return message_desc;
		}
		
	} // namespace Core
} // namespace UnknownEngine
