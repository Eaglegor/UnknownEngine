/*
 * EntitiesParser.cpp
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#include <EntitiesLoader.h>
#include <SupportedTags.h>
#include <XmlSceneLoader.h>
#include <ConstantsHolder.h>
#include <TemplatesManager.h>

namespace UnknownEngine
{
	namespace Loader
	{

        using namespace boost::property_tree;

		EntitiesLoader::~EntitiesLoader()
		{
            // TODO Auto-generated destructor stub
        }

        void EntitiesLoader::loadEntities(const ptree &entities_node)
        {
            scene_loader->getConstantsHolder()->pushScope();
            for(const ptree::value_type &iter : entities_node){
                if(iter.first == Tags::ENTITY){
                    const std::string name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::ENTITY::NAME);
                    loadEntity(name, iter.second);
                }
                else if(iter.first == Tags::TEMPLATED_ENTITY){
                    const std::string name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::TEMPLATED_ENTITY::NAME);
                    const std::string template_name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::TEMPLATED_ENTITY::TEMPLATE_NAME);
                    loadEntity(name, scene_loader->getTemplatesManager()->getTemplate(template_name));
                }
                else if(iter.first == Tags::CONSTANT){
                    scene_loader->getConstantsHolder()->parseAndSaveConstant(iter.second);
                }
            }
            scene_loader->getConstantsHolder()->popScope();
        }

        bool EntitiesLoader::loadEntity(const std::string &name, const ptree &entity_node)
        {
            scene_loader->getConstantsHolder()->pushScope();
            for(const ptree::value_type &iter : entity_node){
                if(iter.first == Tags::COMPONENT){
                    const std::string name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::COMPONENT::NAME);
                    loadComponent(name, iter.second);
                }
                if(iter.first == Tags::TEMPLATED_COMPONENT){
                    const std::string name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::TEMPLATED_COMPONENT::NAME);
                    const std::string template_name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::TEMPLATED_COMPONENT::TEMPLATE_NAME);
                    loadComponent(name, scene_loader->getTemplatesManager()->getTemplate(template_name));
                }
                else if(iter.first == Tags::CONSTANT){
                    scene_loader->getConstantsHolder()->parseAndSaveConstant(iter.second);
                }
            }
            scene_loader->getConstantsHolder()->popScope();
        }

        bool EntitiesLoader::loadComponent(const std::string &name, const ptree &component_node)
        {
            scene_loader->getConstantsHolder()->pushScope();
            scene_loader->getConstantsHolder()->popScope();
        }

        bool EntitiesLoader::createDataProvider(const std::string &name, const ptree &data_provider_node)
        {
            scene_loader->getConstantsHolder()->pushScope();
            scene_loader->getConstantsHolder()->popScope();
        }

	} /* namespace Core */
} /* namespace UnknownEngine */
