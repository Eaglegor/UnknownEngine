/*
 * TemplatesManager.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <unordered_map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <InlineSpecification.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Loader
	{
		class TemplateNotFound : public Core::Exception{ public: TemplateNotFound(const std::string &reason):Core::Exception(reason){} };

		class TemplatesManager
		{
			public:
				TemplatesManager();
				virtual ~TemplatesManager();

				UNKNOWNENGINE_INLINE
				void loadTemplate(const std::string &template_name, const std::string &filename)
				{
					boost::property_tree::ptree template_root;
					boost::property_tree::read_xml(filename, template_root);
					templates[template_name] = template_root;
				}

				UNKNOWNENGINE_INLINE
				boost::property_tree::ptree getTemplate(const std::string &template_name) throw (TemplateNotFound)
				{
					auto found = templates.find(template_name);
					if(found==templates.end()) throw TemplateNotFound("Requested template not found");
					return found->second;
				}

				std::unordered_map<std::string, boost::property_tree::ptree> templates;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
