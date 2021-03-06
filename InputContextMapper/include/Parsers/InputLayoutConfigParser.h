#pragma once

#include <string>
#include <istream>
#include <boost/property_tree/ptree_fwd.hpp>
#include <Parsers/KeycodeParser.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ILogger;
	}

	namespace IO
	{

		class InputContextMapper;
		
		class InputLayoutConfigParser
		{
		public:
			InputLayoutConfigParser(InputContextMapper* context_mapper, Core::LogHelper &logger);
			
			void processConfig(const std::string &filename);
			void processConfig(std::istream& input_stream);
			
		private:
		
			enum class SubscriptionType
			{
				MOUSE_AXIS,
				MOUSE_BUTTON,
				JOYSTICK_AXIS,
				JOYSTICK_BUTTON,
				KEYBOARD
			};
			
			void processSection(const std::string &name, const boost::property_tree::ptree &node);
			void processSubscription(const std::string &section_name, const std::string &name, const std::string &subscription_desc);
			
			SubscriptionType determineSubscriptionType(const std::string& subscription_desc);
			
			void processMouseAxisSubscription(const std::string &section_name, const std::string &name, const std::string& subscription_desc);
			void processMouseButtonSubscription(const std::string &section_name, const std::string &name, const std::string& subscription_desc);
			void processJoystickAxisSubscription(const std::string &section_name, const std::string &name, const std::string& subscription_desc);
			void processJoystickButtonSubscription(const std::string &section_name, const std::string &name, const std::string& subscription_desc);
			void processKeyboardSubscription(const std::string &section_name, const std::string &name, const std::string& subscription_desc);
			
			KeycodeParser keycode_parser;
			InputContextMapper* context_mapper;
			Core::LogHelper &logger;
		};
	}
}