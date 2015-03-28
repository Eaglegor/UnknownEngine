#pragma once

#include <string>
#include <boost/optional.hpp>
#include <Descriptors/OgreRenderWindowDescriptor.h>
#include <Descriptors/DescriptorUtils.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		struct OgreRenderSubsystemDescriptor : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			Utils::OptionalProperty<std::string> ogre_plugins_filename;
			Utils::OptionalProperty<std::string> ogre_config_filename;
			Utils::OptionalProperty<std::string> ogre_log_filename;

			Utils::OptionalProperty<std::string> ogre_resources_filename;

			Utils::OptionalProperty<Core::LogSeverity> log_level;
			
			Utils::OptionalProperty<bool> show_config_dialog;

			OgreRenderSubsystemDescriptor() :
				ogre_plugins_filename ( "plugins.cfg" ),
				ogre_config_filename ( "ogre.cfg" ),
				ogre_log_filename ( "Ogre.log" ),
				log_level(Core::LogSeverity::NONE)
			{
				UEDESC_ADD_FIELD(ogre_plugins_filename);
				UEDESC_ADD_FIELD(ogre_config_filename);
				UEDESC_ADD_FIELD(ogre_log_filename);
				
				UEDESC_ADD_FIELD(ogre_resources_filename);
				UEDESC_ADD_FIELD(log_level);
				UEDESC_ADD_FIELD(show_config_dialog);
			}

		};
	}
}
