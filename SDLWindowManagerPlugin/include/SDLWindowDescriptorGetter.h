#pragma once
#include <boost/variant/static_visitor.hpp>
#include <SDLWindowManagerDescriptor.h>
#include <DescriptorContainer.h>
#include <Properties/Properties_fwd.h>
#include <CommonParsers/PropertiesParser.h>
#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace GUI
	{

		class SDLWindowDescriptorGetter : public boost::static_visitor<SDLWindowDesc>
		{
			public:
				SDLWindowDesc operator() ( const Core::DescriptorContainer& descriptor_container ) const
				{
					return descriptor_container.get<SDLWindowDesc>();
				}

				SDLWindowDesc operator() ( const Core::Properties &properties ) const
				{
					SDLWindowDesc desc;

					using Utils::PropertiesParser;

					PropertiesParser::parse
					(
					    properties,
					{

						{"width", PropertiesParser::RequiredValue<size_t> ( desc.width ) },
						{"height", PropertiesParser::RequiredValue<size_t> ( desc.height ) },
						{"window_title", PropertiesParser::OptionalValue <std::string> ( desc.window_title ) },
						{"resizable", PropertiesParser::OptionalValue <bool> ( desc.resizable ) },
						{"fullscreen", PropertiesParser::OptionalValue <bool> ( desc.full_screen ) },
						{"log_level", PropertiesParser::OptionalValue <Core::LogSeverity> ( desc.log_level ) },
						{
							"update_frame_provider_name", PropertiesParser::RequiredValue<std::string> ( [&desc] ( const std::string & value )
							{
								desc.update_frame_provider = Core::ComponentsManager::getSingleton()->findComponent ( value.c_str() );
							}
							)
						}
					}
					);

					return desc;
				}
		};

	}
}
