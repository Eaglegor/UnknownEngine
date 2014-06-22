/*
 * XmlSceneLoader.cpp
 *
 *  Created on: 22 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <ConstantsHolder.h>
#include <TemplatesManager.h>
#include <SubsystemsLoader.h>
#include <EntitiesLoader.h>

#include <XmlSceneLoader.h>

namespace UnknownEngine
{
	namespace Loader
	{

		static const std::string XMLATTR = "<xmlattr>";

		using namespace boost::property_tree;
		typedef std::exception InvalidSceneFile;

		XmlSceneLoader::XmlSceneLoader(std::string filename) :
				filename(filename),
				templates_manager(nullptr),
				constants_holder(nullptr)
		{
		}

		XmlSceneLoader::~XmlSceneLoader()
		{
			if(constants_holder) delete constants_holder;
			if(templates_manager) delete templates_manager;
		}

		void XmlSceneLoader::loadScene(Core::ComponentsManager* components_manager, Core::PluginsManager* plugins_manager)
		{
			ptree xml_tree;
			read_xml(filename, xml_tree);

			boost::optional<ptree&> scene_root = xml_tree.get_child_optional("scene");
			if (!scene_root.is_initialized())
			{
				throw InvalidSceneFile();
			}

			boost::optional<ptree&> engine_settings = xml_tree.get_child_optional("engine");
			if (engine_settings.is_initialized())
			{
				processEngineSettings(engine_settings.get());
			}

			boost::optional<ptree&> subsystems_list = xml_tree.get_child_optional("subsystems");
			if (subsystems_list.is_initialized())
			{
				processSubsystems(subsystems_list.get(), plugins_manager);
			}

			boost::optional<ptree&> entities_list = xml_tree.get_child_optional("entities");
			if (entities_list.is_initialized())
			{
				processEntities(entities_list.get(), components_manager);
			}

		}

		void XmlSceneLoader::processEngineSettings(const boost::property_tree::ptree& node)
		{
			boost::optional<const ptree&> templates_list = node.get_child_optional("templates");
			if(templates_list.is_initialized()){
				templates_manager = new TemplatesManager();
				for(const ptree::value_type &iter : templates_list.get()){
					if(iter.first=="template"){
						const ptree &attrs = iter.second.get_child(XMLATTR);
						const std::string template_name = attrs.get<std::string>("name");
						const std::string template_filename = attrs.get<std::string>("filename");
						templates_manager->loadTemplate(template_name, template_filename);
					}
				}
			}
		}

		void XmlSceneLoader::processSubsystems(const boost::property_tree::ptree& node, Core::PluginsManager* plugins_manager)
		{
			SubsystemsLoader subsystems_loader(plugins_manager, templates_manager, constants_holder);
			subsystems_loader.loadSubsystems(node);
		}

		void XmlSceneLoader::parseGlobalConstants(const boost::property_tree::ptree& root)
		{
			constants_holder = new ConstantsHolder();
			constants_holder->pushScope();
			for(auto &iter : root){
				if(iter.first=="constant"){
					const ptree &attrs = iter.second.get_child(XMLATTR);
					const std::string constant_name = attrs.get<std::string>("name");
					const std::string constant_value = attrs.get<std::string>("name");
					constants_holder->setConstantValue(constant_name, constant_value);
				}
			}
		}

		void XmlSceneLoader::processEntities(const boost::property_tree::ptree& node, Core::ComponentsManager* components_manager)
		{
			EntitiesLoader entities_loader(components_manager, templates_manager, constants_holder);
			entities_loader.loadEntities(node);
		}

	} /* namespace Loader */
} /* namespace UnknownEngine */
