/*
 * SubsystemsParser.cpp
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <SubsystemsLoader.h>
#include <Plugins/PluginsManager.h>
#include <XmlSceneLoader.h>
#include <SupportedTags.h>
#include <TemplatesManager.h>
#include <MessageListenerParser.h>
#include <SubsystemDesc.h>
#include <OptionsParser.h>
#include <ConstantsHolder.h>

#ifdef _MSC_VER
	#define WIN32_BUILD
#else
	#define LINUX_BUILD
#endif

namespace UnknownEngine
{
	namespace Loader
	{

		using namespace boost::property_tree;

		SubsystemsLoader::~SubsystemsLoader()
		{
			// TODO Auto-generated destructor stub
		}

		void SubsystemsLoader::loadSubsystems ( const boost::property_tree::ptree& node )
		{
			scene_loader->getConstantsHolder()->pushScope();
			for ( auto & iter : node )
			{
				if ( iter.first == Tags::TEMPLATED_SUBSYSTEM )
				{
					const ptree &attrs = iter.second.get_child ( XMLATTR );
					const std::string template_name = attrs.get<std::string> ( Attributes::TEMPLATED_SUBSYSTEM::TEMPLATE_NAME );
					const std::string subsystem_name = attrs.get<std::string> ( Attributes::TEMPLATED_SUBSYSTEM::NAME );
					boost::optional<const ptree &> template_root = scene_loader->getTemplatesManager()->getTemplate ( template_name ).get_child_optional("subsystem");
					if(template_root.is_initialized())
					{
						loadSubsystem (subsystem_name, template_root.get());
					}
					else
					{
						throw InvalidSubsystemTemplate("Can't find <subsystem> tag in template file for templated subsystem '" + subsystem_name + "'");
					}
				}
				else if ( iter.first == Tags::SUBSYSTEM )
				{
					const ptree &attrs = iter.second.get_child ( XMLATTR );
					const std::string subsystem_name = attrs.get<std::string> ( Attributes::SUBSYSTEM::NAME );
					loadSubsystem ( subsystem_name, iter.second );
				}
				else if ( iter.first == Tags::CONSTANT )
				{
					scene_loader->getConstantsHolder()->parseAndSaveConstant ( iter.second );
				}
			}

			scene_loader->getPluginsManager()->initSubsystems();

			scene_loader->getConstantsHolder()->popScope();
		}

		void SubsystemsLoader::loadSubsystem ( const std::string &name, const boost::property_tree::ptree& node )
		{
			scene_loader->getConstantsHolder()->pushScope();
			Core::SubsystemDesc desc;
			desc.name = name;
			
#ifdef WIN32_BUILD
			desc.module_name = node.get_child ( XMLATTR ).get<std::string> ( Attributes::SUBSYSTEM::MODULE ) + ".dll";
#else
			desc.module_name = "lib" + node.get_child ( XMLATTR ).get<std::string> ( Attributes::SUBSYSTEM::MODULE ) + ".so";
#endif
			
			for ( auto & iter : node )
			{
				if ( iter.first == Tags::MESSAGE_LISTENER )
				{
					desc.received_messages = MessageListenerParser::parseMessageListener ( iter.second, scene_loader->getConstantsHolder() );
				}
				else if ( iter.first == Tags::OPTIONS_SECTION )
				{
					desc.descriptor = OptionsParser::parseOptions ( iter.second, scene_loader->getConstantsHolder() );
				}
				else if ( iter.first == Tags::CONSTANT )
				{
					scene_loader->getConstantsHolder()->parseAndSaveConstant ( iter.second );
				}
			}
			
			plugins_manager->loadSubsystem ( desc );
			scene_loader->getConstantsHolder()->popScope();
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
