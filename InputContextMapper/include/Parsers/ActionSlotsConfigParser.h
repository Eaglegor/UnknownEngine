#pragma once

#include <Exception.h>
#include <boost/property_tree/ptree_fwd.hpp>
#include <istream>
#include <string>
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
		class InputContext;
		
		class ActionSlotsConfigParser
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(InvalidActionSlotsConfigFileFormat);
			
			ActionSlotsConfigParser(InputContextMapper* context_mapper, Core::LogHelper &logger);
			
			void processConfig(const std::string &filename);
			void processConfig(std::istream& input_stream);
			
		private:
			void processContext(const boost::property_tree::ptree& node);
			void processActionSlot(InputContext* input_context, const boost::property_tree::ptree& node);
			
			InputContextMapper* context_mapper;
			Core::LogHelper &logger;
		};
	}
}