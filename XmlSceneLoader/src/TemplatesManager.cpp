#include <stdafx.h>

#include <TemplatesManager.h>
#include <SupportedTags.h>

namespace UnknownEngine
{
	namespace Loader
	{

		TemplatesManager::TemplatesManager()
		{
			// TODO Auto-generated constructor stub

		}

		TemplatesManager::~TemplatesManager()
		{
			// TODO Auto-generated destructor stub
		}

		void TemplatesManager::loadTemplate( const std::string &template_name, const std::string &filename )
		{
			if(aliases.find(template_name) != aliases.end())
			{
				throw DuplicateTemplateAliasName("Duplicate template alias found while loading scene file. Template with alias '" + template_name+"' already exists");
			}

			boost::property_tree::ptree template_root;
			boost::property_tree::read_xml ( filename, template_root );
			templates[filename] = template_root;
			aliases[template_name] = filename;
			loaded_template_files.insert(filename);

			// Recursive loading template dependencies
			for(const boost::property_tree::ptree::value_type &child_node: template_root)
			{
				if(child_node.first == Tags::TEMPLATE)
				{
					const boost::property_tree::ptree &attrs = child_node.second.get_child ( XMLATTR );
					const std::string template_name = attrs.get<std::string> ( Attributes::TEMPLATE::NAME );
					const std::string template_filename = attrs.get<std::string> ( Attributes::TEMPLATE::FILENAME );

					if(loaded_template_files.find(template_filename) == loaded_template_files.end())
					{
						loadTemplate(template_name, template_filename);
					}
					aliases[template_name] = template_filename;
				}
			}
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
