#pragma once
#include <boost/variant/static_visitor.hpp>
#include <SDLWindowManagerDescriptor.h>
#include <DescriptorContainer.h>
#include <Properties/Properties_fwd.h>
#include <CommonParsers/PropertiesParser.h>
#include <CommonParsers/LexicalCastForBoolAlpha.h>

namespace UnknownEngine
{
	namespace GUI
	{

		class SDLWindowManagerDescriptorGetter : public boost::static_visitor<SDLWindowManagerDescriptor>
		{
			public:
				SDLWindowManagerDescriptor operator() ( const Core::DescriptorContainer& descriptor_container ) const
				{
					if(descriptor_container.isEmpty()) return SDLWindowManagerDescriptor();
					return descriptor_container.get<SDLWindowManagerDescriptor>();
				}

				SDLWindowManagerDescriptor operator() ( const Core::Properties &properties ) const
				{
					SDLWindowManagerDescriptor desc;

					using Utils::PropertiesParser;

					PropertiesParser::parse
					(
					    properties,
					{
						{
							"RenderWindow",
							PropertiesParser::RequiredNestedValue
							( {
								{"width", PropertiesParser::RequiredValue<size_t> ( desc.window_desc.width ) },
								{"height", PropertiesParser::RequiredValue<size_t> ( desc.window_desc.height ) },
								{"window_name", PropertiesParser::RequiredValue <std::string> ( desc.window_desc.window_name ) },
								{"window_title", PropertiesParser::OptionalValue <std::string> ( desc.window_desc.window_title ) },
								{"resizable", PropertiesParser::OptionalValue <bool> ( desc.window_desc.resizable ) },
								{"fullscreen", PropertiesParser::OptionalValue <bool> ( desc.window_desc.full_screen ) },
								{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity>(desc.log_level)}
							} )
						}
					}
					);

					return desc;
				}
		};

	}
}
