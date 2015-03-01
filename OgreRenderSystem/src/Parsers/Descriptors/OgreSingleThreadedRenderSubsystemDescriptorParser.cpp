#include <stdafx.h>

#include <Parsers/Descriptors/OgreRenderSubsystemDescriptorParser.h>
#include <Parsers/Descriptors/OgreSingleThreadedRenderSubsystemDescriptorParser.h>
#include <Parsers/Descriptors/OgreRenderWindowDescriptorParser.h>
#include <Descriptors/OgreRenderWindowDescriptor.h>

#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <CommonParsers/PropertiesParser.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreSingleThreadedRenderSubsystemDescriptor OgreSingleThreadedRenderSubsystemDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreSingleThreadedRenderSubsystemDescriptor desc;
			desc.base_descriptor = OgreRenderSubsystemDescriptorParser::parse(properties);;
			
			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				properties,
				{
					{"update_frame_provider_name", PropertiesParser::OptionalValue<std::string>([&desc](const std::string& value){
						desc.update_frame_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
					}
					)}
					
				}
			);
			
			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
