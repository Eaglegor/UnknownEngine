#include <stdafx.h>
#include <Parsers/InputLayoutConfigParser.h>
#include <InputContextMapper.h>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <Logging.h>

namespace UnknownEngine 
{
	namespace IO
	{
		
		using namespace boost::property_tree;
		
		InputLayoutConfigParser::InputLayoutConfigParser ( InputContextMapper* context_mapper, Core::ILogger* logger ):
		context_mapper(context_mapper),
		logger(logger)
		{
		}

		void InputLayoutConfigParser::processConfig ( const std::string& filename )
		{
			LOG_INFO(logger, "Processing input layout config file: " + filename);
			std::fstream file(filename);
			processConfig(file);
		}

		void InputLayoutConfigParser::processConfig ( std::istream& input_stream )
		{
			ptree props;
			
			LOG_INFO(logger, "Parsing file");
			read_ini(input_stream, props);
			
			BOOST_FOREACH(const ptree::value_type& v, props)
			{
				processSection(v.first, v.second);
			}
			
		}
		
		void InputLayoutConfigParser::processSection ( const std::string& name, const ptree& node )
		{
			LOG_INFO(logger, "Processing input context layout: " + name);
			
			std::vector<std::string> multiple_subscriptions;
			
			BOOST_FOREACH(const ptree::value_type& v, node)
			{
				std::string subscriptions = v.second.get_value<std::string>();
				
				boost::algorithm::split ( multiple_subscriptions, subscriptions, boost::algorithm::is_any_of("/"), boost::algorithm::token_compress_on);
				
				for(std::string& subscription : multiple_subscriptions)
				{
					boost::algorithm::trim(subscription);
					processSubscription(name, v.first, subscription);
				}
			}
		}
		
		void InputLayoutConfigParser::processSubscription ( const std::string& section_name, const std::string& name, const std::string& subscription_desc )
		{
			LOG_INFO(logger, "Processing input subscription: " + section_name + "." + name);
			
			SubscriptionType subscription_type = determineSubscriptionType(subscription_desc);
			switch(subscription_type)
			{
				case SubscriptionType::KEYBOARD:
				{
					LOG_DEBUG(logger, "Keyboard subscription detected");
					processKeyboardSubscription(section_name, name, subscription_desc);
					break;
				}
				case SubscriptionType::MOUSE_AXIS:
				{
					LOG_DEBUG(logger, "Mouse axis subscription detected");
					processMouseAxisSubscription(section_name, name, subscription_desc);
					break;
				}
				case SubscriptionType::MOUSE_BUTTON:
				{
					LOG_DEBUG(logger, "Mouse button subscription detected");
					processMouseButtonSubscription(section_name, name, subscription_desc);
					break;
				}
				case SubscriptionType::JOYSTICK_AXIS:
				{
					LOG_DEBUG(logger, "Joystick axis subscription detected");
					processJoystickAxisSubscription(section_name, name, subscription_desc);
					break;
				}
				case SubscriptionType::JOYSTICK_BUTTON:
				{
					LOG_DEBUG(logger, "Joystick button subscription detected");
					processJoystickButtonSubscription(section_name, name, subscription_desc);
					break;
				}
			}
		}
		
		InputLayoutConfigParser::SubscriptionType InputLayoutConfigParser::determineSubscriptionType ( const std::string& subscription_desc )
		{
			auto result = boost::algorithm::find_first(subscription_desc, "MouseAxis");
			if(result)
			{
				return SubscriptionType::MOUSE_AXIS;
			}
			result = boost::algorithm::find_first(subscription_desc, "MouseButton");
			if(result)
			{
				return SubscriptionType::MOUSE_BUTTON;
			}
			result = boost::algorithm::find_first(subscription_desc, "JoystickButton");
			if(result)
			{
				return SubscriptionType::JOYSTICK_BUTTON;
			}
			result = boost::algorithm::find_first(subscription_desc, "JoystickAxis");
			if(result)
			{
				return SubscriptionType::JOYSTICK_AXIS;
			}
			return SubscriptionType::KEYBOARD;
		}
		
		void InputLayoutConfigParser::processMouseAxisSubscription ( const std::string& section_name, const std::string& name, const std::string& subscription_desc )
		{
			std::vector<std::string> split_value;
			boost::algorithm::split ( split_value, subscription_desc, boost::algorithm::is_any_of ( "(,: )" ), boost::algorithm::token_compress_on );

			size_t mouse_id;
			size_t mouse_axis_id;

			for ( size_t i = 1; i < split_value.size(); i += 2 )
			{
				if ( split_value[i] == "mid" )
				{
					mouse_id = boost::lexical_cast<size_t> ( split_value[i + 1] );
				}
				if ( split_value[i] == "axis" )
				{
					mouse_axis_id = boost::lexical_cast<size_t> ( split_value[i + 1] );
				}
			}

			switch(mouse_axis_id)
			{
				case 0:
				{
					LOG_DEBUG(logger, "Subscription details parsed: mouse axis X");
					context_mapper->getMouseEventHandler()->addActionSlotSubscription(section_name, name, MouseAxis::X);
					break;
				}
				case 1:
				{
					LOG_DEBUG(logger, "Subscription details parsed: mouse axis Y");
					context_mapper->getMouseEventHandler()->addActionSlotSubscription(section_name, name, MouseAxis::Y);
					break;
				}
				case 2:
				{
					LOG_DEBUG(logger, "Subscription details parsed: mouse axis Z");
					context_mapper->getMouseEventHandler()->addActionSlotSubscription(section_name, name, MouseAxis::Z);
					break;
				}
			}
			
		}
		
		void InputLayoutConfigParser::processMouseButtonSubscription ( const std::string& section_name, const std::string& name, const std::string& subscription_desc )
		{
			std::vector<std::string> split_value;
			boost::algorithm::split ( split_value, subscription_desc, boost::algorithm::is_any_of ( "(,: )" ), boost::algorithm::token_compress_on );

			size_t mouse_id;
			size_t mouse_button_id;

			for ( size_t i = 1; i < split_value.size(); i += 2 )
			{
				if ( split_value[i] == "mid" )
				{
					mouse_id = boost::lexical_cast<size_t> ( split_value[i + 1] );
				}
				if ( split_value[i] == "button" )
				{
					mouse_button_id = boost::lexical_cast<size_t> ( split_value[i + 1] );
				}
			}

			LOG_DEBUG(logger, "Subscription details parsed: mouse button " + std::to_string(mouse_button_id));
			context_mapper->getMouseEventHandler()->addActionSlotSubscription(section_name, name, mouse_button_id);
			
		}
		
		void InputLayoutConfigParser::processJoystickAxisSubscription ( const std::string& section_name, const std::string& name, const std::string& subscription_desc )
		{
			std::vector<std::string> split_value;
			boost::algorithm::split ( split_value, subscription_desc, boost::algorithm::is_any_of ( "(,: )" ), boost::algorithm::token_compress_on );

			size_t joystick_id;
			size_t joystick_axis_id;

			for ( size_t i = 1; i < split_value.size(); i += 2 )
			{
				if ( split_value[i] == "jid" )
				{
					joystick_id = boost::lexical_cast<size_t> ( split_value[i + 1] );
				}
				if ( split_value[i] == "axis" )
				{
					joystick_axis_id = boost::lexical_cast<size_t> ( split_value[i + 1] );
				}
			}

			LOG_DEBUG(logger, "Subscription details parsed: joystick axis: " + std::to_string(joystick_axis_id));
			context_mapper->getJoystickEventHandler()->addAxisActionSlotSubscription(section_name, name, joystick_axis_id);
			
		}
		
		void InputLayoutConfigParser::processJoystickButtonSubscription ( const std::string& section_name, const std::string& name, const std::string& subscription_desc )
		{
			std::vector<std::string> split_value;
			boost::algorithm::split ( split_value, subscription_desc, boost::algorithm::is_any_of ( "(,: )" ), boost::algorithm::token_compress_on );

			size_t joystick_id;
			size_t joystick_button_id;

			for ( size_t i = 1; i < split_value.size(); i += 2 )
			{
				if ( split_value[i] == "jid" )
				{
					joystick_id = boost::lexical_cast<size_t> ( split_value[i + 1] );
				}
				if ( split_value[i] == "button" )
				{
					joystick_button_id = boost::lexical_cast<size_t> ( split_value[i + 1] );
				}
			}

			LOG_DEBUG(logger, "Subscription details parsed: joystick button " + std::to_string(joystick_button_id));
			context_mapper->getMouseEventHandler()->addActionSlotSubscription(section_name, name, joystick_button_id);
			
		}
		
		void InputLayoutConfigParser::processKeyboardSubscription ( const std::string& section_name, const std::string& name, const std::string& subscription_desc )
		{
			Key key = keycode_parser.parse( boost::algorithm::to_upper_copy(subscription_desc));
			LOG_DEBUG(logger, "Subscription details parsed: key " + subscription_desc);
			context_mapper->getKeyboardEventHandler()->addActionSlotSubscription(section_name, name, key);
		}
		
	}
}