#include <stdafx.h>
#include <CommonParsers/PropertiesParser.h>

#include <Parsers/Descriptors/OgreRenderWindowDescriptorParser.h>
#include <ComponentSystem/ComponentsManager.h>
#include <Logging.h>

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
					{"height", PropertiesParser::OptionalValue <size_t> ( desc.height )},
					{"log_level", PropertiesParser::OptionalValue <Core::LogSeverity> ( desc.log_level )},
					{"parent_window_component_name", PropertiesParser::OptionalValue<std::string>([&desc](const std::string& value){
						desc.parent_window = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
					}
					)}
				}
			);

			return desc;

		}
	}
}