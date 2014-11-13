#pragma once

#include <boost/variant.hpp>
#include <Descriptors/SimpleBehaviorsPluginDesc.h>
#include <CommonParsers/PropertiesParser.h>
#include <DescriptorContainer.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class SimpleBehaviorsPluginDescriptorGetter : public boost::static_visitor<SimpleBehaviorsPluginDesc>
		{
			public:
				SimpleBehaviorsPluginDesc operator() ( const Core::DescriptorContainer& descriptor ) const
				{
					if ( descriptor.isEmpty() ) return SimpleBehaviorsPluginDesc();
					return descriptor.get<SimpleBehaviorsPluginDesc>();
				}

				SimpleBehaviorsPluginDesc operator() ( const Core::Properties &properties ) const
				{
					SimpleBehaviorsPluginDesc desc;

					using Utils::PropertiesParser;

					Utils::PropertiesParser properties_parser;
					properties_parser.parse (
					    properties,
					{
						{"log_level", PropertiesParser::OptionalValue<Utils::LogSeverity> ( desc.log_level ) }
					}
					);

					return desc;
				}
		};
	}
}
