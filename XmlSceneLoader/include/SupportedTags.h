#pragma once

#include <string>

namespace UnknownEngine
{
	namespace Loader
	{
		static const std::string XMLATTR = "<xmlattr>";

		namespace Tags
		{
			static const std::string SCENE = "scene";
			static const std::string ENGINE_SECTION = "engine";
			static const std::string TEMPLATES_SECTION = "templates";
			static const std::string TEMPLATE = "template";
			static const std::string CONSTANT = "constant";
			static const std::string SUBSYSTEMS_SECTION = "subsystems";
			static const std::string SUBSYSTEM = "subsystem";
			static const std::string MESSAGE_LISTENER = "message_listener";
			static const std::string MESSAGE = "message";
			static const std::string RECEIVE_POLICY = "receive_policy";
			static const std::string OPTIONS_SECTION = "options_section";
			static const std::string OPTION = "option";
			static const std::string DATA_PROVIDER = "data_provider";
			static const std::string COMPONENT = "component";
			static const std::string ENTITIES_SECTION = "entities";
			static const std::string ENTITY = "entity";
			static const std::string TEMPLATED_ENTITY = "templated_entity";
			static const std::string TEMPLATED_SUBSYSTEM = "templated_subsystem";
			static const std::string TEMPLATED_COMPONENT = "templated_component";
			static const std::string TEMPLATED_OPTIONS_SECTION = "templated_options";
		}

		namespace Attributes
		{
			namespace SCENE
			{
			}
			namespace ENGINE_SECTION
			{
			}
			namespace TEMPLATES_SECTION
			{
			}
			namespace TEMPLATE
			{
				static const std::string NAME = "name";
				static const std::string FILENAME = "filename";
			}
			namespace CONSTANT
			{
				static const std::string NAME = "name";
				static const std::string VALUE = "value";
			}
			namespace SUBSYSTEMS_SECTION
			{
			}
			namespace SUBSYSTEM
			{
				static const std::string NAME = "name";
				static const std::string MODULE = "module";
			}
			namespace MESSAGE_LISTENER
			{
				static const std::string NAME = "name";
			}
			namespace MESSAGE
			{
				static const std::string EVENT_TYPE = "event_type";
			}
			namespace RECEIVE_POLICY
			{
				static const std::string TYPE = "type";
			}
			namespace OPTIONS_SECTION
			{
				static const std::string NAME = "name";
			}
			namespace OPTION
			{
				static const std::string NAME = "name";
				static const std::string VALUE = "value";
			}
			namespace DATA_PROVIDER
			{
				static const std::string NAME = "name";
				static const std::string TYPE = "type";
			}
			namespace COMPONENT
			{
				static const std::string TYPE = "type";
				static const std::string NAME = "name";
			}
			namespace ENTITIES_SECTION
			{
			}
			namespace ENTITY
			{
				static const std::string NAME = "name";
			}
			namespace TEMPLATED_ENTITY
			{
				static const std::string NAME = "name";
				static const std::string TEMPLATE_NAME = "template_name";
			}
			namespace TEMPLATED_SUBSYSTEM
			{
				static const std::string NAME = "name";
				static const std::string TEMPLATE_NAME = "template_name";
			}
			namespace TEMPLATED_COMPONENT
			{
				static const std::string NAME = "name";
				static const std::string TEMPLATE_NAME = "template_name";
			}
			namespace TEMPLATED_OPTIONS_SECTION
			{
				static const std::string NAME = "name";
				static const std::string TEMPLATE_NAME = "template_name";
			}
		}

	}
}
