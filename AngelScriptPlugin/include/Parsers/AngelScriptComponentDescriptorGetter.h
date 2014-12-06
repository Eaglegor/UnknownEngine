#pragma once
#include <Descriptors/AngelScriptComponentDesc.h>
#include <DescriptorContainer.h>
#include <boost/variant/static_visitor.hpp>
#include <Exception.h>
#include <Properties/Properties_fwd.h>
#include <CommonParsers/PropertiesParser.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class AngelScriptComponentDescriptorGetter : public boost::static_visitor<AngelScriptComponentDesc>
		{
		public:
			
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoDescriptorProvided);
			
			AngelScriptComponentDesc operator()(const Core::DescriptorContainer &container) const
			{
				if(container.isEmpty())
				{
					throw NoDescriptorProvided("No descriptor provided to create component");
				}
				else
				{
					return container.get<AngelScriptComponentDesc>();
				}
			}
			
			AngelScriptComponentDesc operator()(const Core::Properties& props) const
			{
				AngelScriptComponentDesc desc;
				
				using Utils::PropertiesParser;
				
				PropertiesParser parser;
				
				parser.parse(
					props,
					{
						{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity>(desc.log_level)},
						{"script_filename", PropertiesParser::RequiredValue<std::string>(desc.script_filename)}
					}
				);
				
				return desc;
			}
			
		};
	}
}