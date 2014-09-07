#include <SDLWindowManagerDescriptorParser.h>
#include <Properties/Properties.h>
#include <CommonParsers/PropertiesParser.h>
#include <CommonParsers/LexicalCastForBoolAlpha.h>

namespace UnknownEngine
{
	namespace GUI
	{
		SDLWindowManagerDescriptor SDLWindowManagerDescriptorParser::parse ( const Core::Properties& properties )
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
					({
						{"width", PropertiesParser::RequiredValue<size_t>( desc.window_desc.width ) },
						{"height", PropertiesParser::RequiredValue<size_t>( desc.window_desc.height ) },
						{"window_name", PropertiesParser::RequiredValue <std::string> (desc.window_desc.window_name ) },
						{"window_title", PropertiesParser::OptionalValue <std::string> (desc.window_desc.window_title) },
						{"resizable", PropertiesParser::OptionalValue <bool> (desc.window_desc.resizable) },
						{"fullscreen", PropertiesParser::OptionalValue <bool> (desc.window_desc.full_screen) }
					})
					}
				}
			);
			
			return desc;
		}
	}
}