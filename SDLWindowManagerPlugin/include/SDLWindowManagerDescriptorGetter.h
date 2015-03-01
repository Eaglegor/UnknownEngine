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

		class SDLWindowManagerDescriptorGetter : public boost::static_visitor<SDLWindowManagerDescriptor>
		{
			public:
				SDLWindowManagerDescriptor operator() ( const Core::DescriptorContainer& descriptor_container ) const
				{
					if ( descriptor_container.isEmpty() ) return SDLWindowManagerDescriptor();
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
						{"log_level", PropertiesParser::OptionalValue<Core::LogSeverity> ( desc.log_level ) }
					}
					);

					return desc;
				}
		};

	}
}
