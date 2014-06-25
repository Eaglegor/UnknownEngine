/*
 * TemplatesManager.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#ifndef TEMPLATESMANAGER_H_
#define TEMPLATESMANAGER_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <map>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Loader
	{
		class TemplateNotFound : public Core::Exception{};

		class TemplatesManager
		{
			public:
				TemplatesManager();
				virtual ~TemplatesManager();

				void loadTemplate(std::string template_name, std::string filename)
				{
					boost::property_tree::ptree template_root;
					boost::property_tree::read_xml(filename, template_root);
					templates[template_name] = template_root;
				}

				boost::property_tree::ptree getTemplate(std::string template_name) throw (TemplateNotFound)
				{
					auto found = templates.find(template_name);
					if(found==templates.end()) throw TemplateNotFound();
					return found->second;
				}

				std::map<std::string, boost::property_tree::ptree> templates;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* TEMPLATESMANAGER_H_ */
