#pragma once

#include <string>
#include <boost/optional.hpp>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct OgreRenderSubsystemDescriptor
		{
			struct RenderWindowDescriptor
			{
				
				
				std::string name;
				
			};
			
			std::string ogre_plugins_filename;
			std::string ogre_config_filename;
			std::string ogre_log_filename;
			std::string render_window_name;
			std::string ogre_resources_filename;
			
			Core::LogMessage::Severity log_level;

			bool separate_rendering_thread;

			bool show_config_dialog;

			OgreRenderSubsystemDescriptor() :
				render_window_name ( "Untitled window" ),
				ogre_config_filename ( "ogre.cfg" ),
				ogre_log_filename ( "Ogre.log" ),
				ogre_plugins_filename ( "plugins.cfg" ),
				show_config_dialog ( false ),
				separate_rendering_thread ( true ),
				log_level(Core::LogMessage::Severity::LOG_SEVERITY_NONE)
			{}

		};
	}
}
