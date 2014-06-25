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
#include <Properties/Properties.h>
#include <OptionsParser.h>
#include <ComponentsManager.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <ComponentDesc.h>

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

		void EntitiesLoader::loadEntity(const std::string &name, const ptree &entity_node)
        {
            scene_loader->getConstantsHolder()->pushScope();

			Core::Entity* entity = components_manager->createEntity(name);

            for(const ptree::value_type &iter : entity_node){
                if(iter.first == Tags::COMPONENT){
                    const std::string name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::COMPONENT::NAME);
					loadComponent(entity, name, iter.second);
                }
                if(iter.first == Tags::TEMPLATED_COMPONENT){
                    const std::string name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::TEMPLATED_COMPONENT::NAME);
                    const std::string template_name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::TEMPLATED_COMPONENT::TEMPLATE_NAME);
					loadComponent(entity, name, scene_loader->getTemplatesManager()->getTemplate(template_name));
                }
                else if(iter.first == Tags::CONSTANT){
                    scene_loader->getConstantsHolder()->parseAndSaveConstant(iter.second);
                }
				else if(iter.first == Tags::DATA_PROVIDER){
					const std::string name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::DATA_PROVIDER::NAME);
					createDataProvider(iter.second);
				}
            }
            scene_loader->getConstantsHolder()->popScope();
        }

		Core::Component* EntitiesLoader::loadComponent(Core::Entity* parent_entity, const std::string &name, const ptree &component_node)
        {
			scene_loader->getConstantsHolder()->pushScope();

			Core::ComponentDesc component_desc;
			component_desc.name = name;
			component_desc.entity = parent_entity;

			const std::string component_type = component_node.get_child(XMLATTR).get<std::string>(Attributes::COMPONENT::TYPE);
			component_desc.type = Core::ComponentType(component_type);

			for(const ptree::value_type &iter : component_node){
				if(iter.first == Tags::MESSAGE_LISTENER){
					const std::string name = iter.second.get_child(XMLATTR).get<std::string>(Attributes::MESSAGE_LISTENER::NAME);
					component_desc.message_listeners_desc.push_back(parseMessageListener(iter.second));
				}
				else if(iter.first == Tags::OPTIONS_SECTION){
					component_desc.creation_options = OptionsParser::parseOptions(iter.second, scene_loader->getConstantsHolder());
				}
				else if(iter.first == Tags::CONSTANT){
					scene_loader->getConstantsHolder()->parseAndSaveConstant(iter.second);
				}
			}

			scene_loader->getConstantsHolder()->popScope();

			return components_manager->createComponent(component_desc);
		}

		Core::MessageListenerDesc EntitiesLoader::parseMessageListener(const ptree &event_listener_node)
		{
			Core::MessageListenerDesc listener_desc;
			listener_desc.name = event_listener_node.get_child(XMLATTR).get<std::string>(Attributes::MESSAGE_LISTENER::NAME);
			for(const ptree::value_type &iter : event_listener_node)
			{
				if(iter.first == Tags::MESSAGE){
					listener_desc.events.push_back(parseMessageDesc(iter.second));
				}
			}
			return listener_desc;
		}

		Core::MessageListenerDesc::MessageDesc EntitiesLoader::parseMessageDesc(const ptree &message_node)
		{
			Core::MessageListenerDesc::MessageDesc message_desc;

			boost::optional<const ptree&> receive_policy = message_node.get_child_optional("receive_policy");
			if(receive_policy.is_initialized())
			{
				message_desc.receive_policy_type_name = receive_policy.get().get_child(XMLATTR).get<std::string>(Attributes::RECEIVE_POLICY::TYPE);
				boost::optional<const ptree&> receive_policy_options = receive_policy.get().get_child_optional("options_section");
				if(receive_policy_options.is_initialized())
				{
					message_desc.receive_policy_options = OptionsParser::parseOptions(receive_policy_options.get(), scene_loader->getConstantsHolder());
				}
			}

			return message_desc;
		}

		bool EntitiesLoader::createDataProvider(const ptree &data_provider_node)
        {
            scene_loader->getConstantsHolder()->pushScope();
            scene_loader->getConstantsHolder()->popScope();
        }

	} /* namespace Core */
} /* namespace UnknownEngine */
