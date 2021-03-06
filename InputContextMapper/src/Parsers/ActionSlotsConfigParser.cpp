#include <stdafx.h>
#include <Parsers/ActionSlotsConfigParser.h>

#include <fstream>
#include <string>
#include <InputContextMapper.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <Logging.h>

namespace UnknownEngine 
{
	namespace IO 
	{
		
		using namespace boost::property_tree;
		
		ActionSlotsConfigParser::ActionSlotsConfigParser ( InputContextMapper* context_mapper, Core::LogHelper &logger ):
		context_mapper(context_mapper),
		logger(logger)
		{
		}
		
		void ActionSlotsConfigParser::processConfig ( const std::string& filename)
		{
			LOG_INFO(logger, "Processing action slots config file: " + filename);
			std::ifstream file(filename, std::ifstream::in);
			processConfig(file);
		}

		void ActionSlotsConfigParser::processConfig ( std::istream& input_stream)
		{
			ptree props;
			
			LOG_INFO(logger, "Parsing xml");
			read_xml(input_stream, props);
			
			boost::optional<ptree&> root = props.get_child_optional("contexts");
			if(!root) {
				LOG_ERROR(logger, "Invalid file format - <contexts> root tag not found");
				throw InvalidActionSlotsConfigFileFormat("No 'contexts' tag found");
			}
			
			BOOST_FOREACH(ptree::value_type &v, root.get())
			{
				if(v.first == "context")
				{
					processContext(v.second);
				}
			}
			
		}
		
		void ActionSlotsConfigParser::processContext ( const ptree& node )
		{
			std::string name = node.get<std::string>("<xmlattr>.name");
			LOG_INFO(logger, "Processing input context: " + name);
			
			InputContext* context = context_mapper->createContext(name);
			
			boost::optional<const ptree&> root = node.get_child_optional("action_slots");
			if(!root)
			{
				LOG_ERROR(logger, "Invalid file format: <action_slots> list not found inside the <context> node");
				throw InvalidActionSlotsConfigFileFormat("No 'action_slots' tag found inside context node");
			}
			
			BOOST_FOREACH(const ptree::value_type &v, root.get())
			{
				if(v.first == "action_slot")
				{
					processActionSlot(context, v.second);
				}
			}
		}
		
		void ActionSlotsConfigParser::processActionSlot ( InputContext* input_context, const ptree& node )
		{
			std::string name = node.get<std::string>("<xmlattr>.name");
			std::string event_type = node.get<std::string>("<xmlattr>.event");
			
			LOG_INFO(logger, "Processing action slot: " + name);
			
			if(event_type == "Simple")
			{
				LOG_DEBUG(logger, "Action slot is a simple action slot");
				std::string event_condition = node.get<std::string>("<xmlattr>.condition");
				SimpleActionSlot::ConditionType condition_type;
				if(event_condition == "EventStarted") condition_type = SimpleActionSlot::ConditionType::EVENT_STARTED;
				else if(event_condition == "EventActive") condition_type = SimpleActionSlot::ConditionType::EVENT_ACTIVE;
				else if(event_condition == "EventEnded") condition_type = SimpleActionSlot::ConditionType::EVENT_ENDED;
				input_context->createSimpleActionSlot(name, condition_type);
			}
			else if(event_type == "Range")
			{
				LOG_DEBUG(logger, "Action slot is a range action slot");
				input_context->createRangeActionSlot(name);
			}
		}
		
	}
}