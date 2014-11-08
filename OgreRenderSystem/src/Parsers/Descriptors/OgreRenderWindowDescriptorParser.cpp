#include <stdafx.h>
#include <CommonParsers/PropertiesParser.h>

#include <Parsers/Descriptors/OgreRenderWindowDescriptorParser.h>

namespace boost
{
	typedef UnknownEngine::Graphics::OgreRenderWindowDescriptor::WindowType RenderWindowType;
	
	template<>
	RenderWindowType lexical_cast<RenderWindowType, std::string>(const std::string& string_value)
	{
		if(string_value == "parent") return RenderWindowType::PARENT;
		if(string_value == "external") return RenderWindowType::EXTERNAL;
		return RenderWindowType::OWN;
	}
}

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreRenderWindowDescriptor OgreRenderWindowDescriptorParser::parse ( const Core::Properties& properties )
		{
			
			using Utils::PropertiesParser;

			OgreRenderWindowDescriptor desc;

			PropertiesParser::parse 
			(
				properties,
				{
					{"window_name", PropertiesParser::OptionalValue <std::string> ( desc.window_name )},
					{"window_title", PropertiesParser::RequiredValue <std::string> ( desc.window_title )},
					{"window_type", PropertiesParser::OptionalValue <OgreRenderWindowDescriptor::WindowType> ( desc.type )},
					{
						"window_flags",
						PropertiesParser::OptionalNestedValue
						(
						{
							{"fullscreen",	PropertiesParser::OptionalValue <bool> (desc.fullscreen)}
						}
						)
					},
					{"width", PropertiesParser::OptionalValue <size_t> ( desc.width )},
					{"height", PropertiesParser::OptionalValue <size_t> ( desc.height )}
				}
			);

			return desc;

		}
	}
}