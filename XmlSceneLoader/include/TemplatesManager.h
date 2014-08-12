/*
 * TemplatesManager.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <unordered_map>
#include <unordered_set>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <InlineSpecification.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Loader
	{
		class TemplateNotFound : public Core::Exception
		{
			public:
				TemplateNotFound ( const std::string &reason ) : Core::Exception ( reason ) {}
		};

		class TemplatesManager
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION(DuplicateTemplateAliasName);

				TemplatesManager();
				virtual ~TemplatesManager();

				void loadTemplate ( const std::string &template_name, const std::string &filename );

				UNKNOWNENGINE_INLINE
				const boost::property_tree::ptree &getTemplate ( const std::string &template_name ) throw ( TemplateNotFound )
				{
					auto found = aliases.find ( template_name );
					if ( found == aliases.end() ) throw TemplateNotFound ( "Requested template not found" );
					return templates[found->second];
				}

			private:
				std::unordered_map<std::string, boost::property_tree::ptree> templates;
				std::unordered_map<std::string, std::string> aliases;
				std::unordered_set<std::string> loaded_template_files;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
