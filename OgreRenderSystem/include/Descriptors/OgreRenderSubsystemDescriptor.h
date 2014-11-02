#pragma once

#include <string>
#include <boost/optional.hpp>
#include <ExportedMessages/LogMessage.h>
#include <Descriptors/OgreRenderWindowDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct OgreRenderSubsystemDescriptor
		{
			
			std::string ogre_plugins_filename;
			std::string ogre_config_filename;
			std::string ogre_log_filename;

			boost::optional<std::string> ogre_resources_filename;
			
			Utils::LogSeverity log_level;

			bool separate_rendering_thread;

			bool show_config_dialog;

			OgreRenderWindowDescriptor render_window_descriptor;
			
			OgreRenderSubsystemDescriptor() :
				ogre_plugins_filename ( "plugins.cfg" ),
				ogre_config_filename ( "ogre.cfg" ),
				ogre_log_filename ( "Ogre.log" ),
				log_level(Utils::LogSeverity::NONE),
				separate_rendering_thread ( true ),
				show_config_dialog ( false )
			{}

		};
	}
}
