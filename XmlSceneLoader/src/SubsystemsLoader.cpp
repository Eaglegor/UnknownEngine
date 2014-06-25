/*
 * SubsystemsParser.cpp
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#include <SubsystemsLoader.h>
#include <Plugins/PluginsManager.h>
#include <XmlSceneLoader.h>
#include <SupportedTags.h>
#include <TemplatesManager.h>

namespace UnknownEngine
{
	namespace Loader
	{

		using namespace boost::property_tree;

		SubsystemsLoader::~SubsystemsLoader()
		{
			// TODO Auto-generated destructor stub
		}

		void SubsystemsLoader::loadSubsystems(const boost::property_tree::ptree& node)
		{
			for(auto &iter : node){
				if(iter.first == Tags::TEMPLATED_SUBSYSTEM){
					const ptree &attrs = iter.second.get_child(XMLATTR);
					const std::string template_name = attrs.get<std::string>(Attributes::TEMPLATED_SUBSYSTEM::TEMPLATE_NAME);
					const std::string subsystem_name = attrs.get<std::string>(Attributes::TEMPLATED_SUBSYSTEM::NAME);
					const ptree &template_root = scene_loader->getTemplatesManager()->getTemplate(template_name);
					if(template_root.begin()->first != Tags::SUBSYSTEM) throw InvalidSubsystemTemplate();
					loadSubsystem(subsystem_name, template_root.begin()->second);
				}
				else if(iter.first == Tags::SUBSYSTEM)
				{
					const ptree &attrs = iter.second.get_child(XMLATTR);
					const std::string subsystem_name = attrs.get<std::string>(Attributes::SUBSYSTEM::NAME);
					loadSubsystem(subsystem_name, iter.second);
				}
			}
		}

		void SubsystemsLoader::loadSubsystem(std::string name, const boost::property_tree::ptree& node)
		{

		}

	} /* namespace Core */
} /* namespace UnknownEngine */
