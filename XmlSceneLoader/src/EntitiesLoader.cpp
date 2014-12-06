/*
 * EntitiesParser.cpp
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <EntitiesLoader.h>
#include <SupportedTags.h>
#include <XmlSceneLoader.h>
#include <ConstantsHolder.h>
#include <TemplatesManager.h>
#include <Properties/Properties.h>
#include <OptionsParser.h>
#include <ComponentsManager.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageListenerParser.h>
#include <ComponentDesc.h>
#include <EngineContext.h>


#include <Objects/Entity.h>
#include <../ResourceManager/include/DataProvider/DataProviderDesc.h>
#include <../ResourceManager/include/DataProvider/IDataProvider.h>
#include <../ResourceManager/include/ResourceManager.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Loader
	{

		using namespace boost::property_tree;

		EntitiesLoader::~EntitiesLoader()
		{
			// TODO Auto-generated destructor stub
		}

		void EntitiesLoader::loadEntities ( const ptree &entities_node )
		{
			scene_loader->getConstantsHolder()->pushScope();
			for ( const ptree::value_type & iter : entities_node )
			{
				if ( iter.first == Tags::ENTITY )
				{
					const std::string name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::ENTITY::NAME );
					loadEntity ( name, iter.second );
				}
				else if ( iter.first == Tags::TEMPLATED_ENTITY )
				{
					const std::string name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::TEMPLATED_ENTITY::NAME );
					const std::string template_name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::TEMPLATED_ENTITY::TEMPLATE_NAME );
					boost::optional<const ptree&> entity_start = scene_loader->getTemplatesManager()->getTemplate ( template_name ).get_child_optional("entity");
					if(entity_start.is_initialized())
					{
						loadEntity ( name, entity_start.get() );
					}
					else
					{
						throw InvalidTemplatedEntityFormat("Can't find <entity> node in templated entity file for templated entity '" + name + "'");
					}
				}
				else if ( iter.first == Tags::CONSTANT )
				{
					scene_loader->getConstantsHolder()->parseAndSaveConstant ( iter.second );
				}
				else if ( iter.first == Tags::DATA_PROVIDER )
				{
					createDataProvider ( iter.second );
				}
			}
			
			for(auto& data_provider : data_providers)
			{
				data_provider.second->release();
			}
			engine_context->getResourceManager()->cleanup();
			
			scene_loader->getConstantsHolder()->popScope();
		}

		void EntitiesLoader::loadEntity ( const std::string &name, const ptree &entity_node )
		{
			scene_loader->getConstantsHolder()->pushScope();

			Core::Entity* entity = engine_context->getComponentsManager()->createEntity ( name );
			for ( const ptree::value_type & iter : entity_node )
			{
				if ( iter.first == Tags::COMPONENT )
				{
					const std::string name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::COMPONENT::NAME );
					loadComponent ( entity, name, iter.second );
				}
				else if ( iter.first == Tags::TEMPLATED_COMPONENT )
				{
					const std::string name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::TEMPLATED_COMPONENT::NAME );
					const std::string template_name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::TEMPLATED_COMPONENT::TEMPLATE_NAME );

					boost::optional<const ptree&> component_start = scene_loader->getTemplatesManager()->getTemplate ( template_name ).get_child_optional("component");
					if(component_start.is_initialized())
					{
						loadComponent ( entity, name, component_start.get() );
					}
					else
					{
						throw InvalidTemplatedComponentFormat("Can't find <component> node in templated component file for templated component'" + name +"'");
					}
				}
				else if ( iter.first == Tags::CONSTANT )
				{
					scene_loader->getConstantsHolder()->parseAndSaveConstant ( iter.second );
				}
				else if ( iter.first == Tags::DATA_PROVIDER )
				{
					createDataProvider ( iter.second );
				}
			}
			
			scene_loader->getConstantsHolder()->popScope();
		}

		Core::IComponent* EntitiesLoader::loadComponent ( Core::Entity* parent_entity, const std::string &name, const ptree &component_node )
		{
			scene_loader->getConstantsHolder()->pushScope();

			Core::ComponentDesc component_desc;
			component_desc.name = parent_entity->getName() + "." + name;

			const std::string component_type = component_node.get_child ( XMLATTR ).get<std::string> ( Attributes::COMPONENT::TYPE );
			component_desc.type = Core::ComponentType ( component_type );

			for ( const ptree::value_type & iter : component_node )
			{
				if ( iter.first == Tags::MESSAGING_RULES )
				{
					MessageListenerParser::MessagingRules rules = MessageListenerParser::parseMessagingRules ( iter.second, scene_loader->getConstantsHolder() );
					component_desc.listener_rules = rules.listener_rules;
					component_desc.sender_rules = rules.sender_rules;
				}
				else if ( iter.first == Tags::OPTIONS_SECTION )
				{
					component_desc.descriptor = OptionsParser::parseOptions ( iter.second, scene_loader->getConstantsHolder(), &data_providers );
				}
				else if ( iter.first == Tags::CONSTANT )
				{
					scene_loader->getConstantsHolder()->parseAndSaveConstant ( iter.second );
				}
			}

			scene_loader->getConstantsHolder()->popScope();

			return parent_entity->createComponent(component_desc);
		}

		bool EntitiesLoader::createDataProvider ( const ptree &data_provider_node )
		{
			scene_loader->getConstantsHolder()->pushScope();
			
			Loader::DataProviderDesc desc;
			desc.name = data_provider_node.get_child(XMLATTR).get<std::string>( Attributes::DATA_PROVIDER::NAME );
			desc.type = data_provider_node.get_child(XMLATTR).get<std::string>( Attributes::DATA_PROVIDER::TYPE );
			
			for( const ptree::value_type &iter : data_provider_node )
			{
				if(iter.first == Tags::CONSTANT)
				{
					scene_loader->getConstantsHolder()->parseAndSaveConstant( iter.second );
				}
				else if (iter.first == Tags::OPTIONS_SECTION)
				{
					desc.descriptor = OptionsParser::parseOptions( iter.second, scene_loader->getConstantsHolder(), &data_providers );
				}
			}

			IDataProvider* data_provider = engine_context->getResourceManager()->createDataProvider(desc);
			data_providers[desc.name] = data_provider;
			data_provider->startLoading();
			
			scene_loader->getConstantsHolder()->popScope();
			return false;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
