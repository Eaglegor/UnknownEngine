#include <stdafx.h>

#include <ConstantsHolder.h>
#include <OptionsParser.h>
#include <SupportedTags.h>

namespace UnknownEngine
{
	namespace Loader
	{

		using namespace boost::property_tree;

		OptionsParser::OptionsParser()
		{
			// TODO Auto-generated constructor stub

		}

		OptionsParser::~OptionsParser()
		{
			// TODO Auto-generated destructor stub
		}

		const Core::Properties OptionsParser::parseOptions ( const boost::property_tree::ptree& options_node, const UnknownEngine::Loader::ConstantsHolder* constants, std::unordered_map< std::string, IDataProvider* > *data_providers_map )
		{
			return parseOptionsSection ( options_node, constants, data_providers_map );
		}

		const Core::Properties OptionsParser::parseOptionsSection ( const ptree &options_node, const ConstantsHolder *constants, std::unordered_map<std::string, IDataProvider*> *data_providers_map )
		{
			Core::Properties result;
			for ( const ptree::value_type & iter : options_node )
			{
				if ( iter.first == Tags::OPTIONS_SECTION )
				{
					const std::string &section_name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::OPTIONS_SECTION::NAME );
					result.set< Core::Properties > ( section_name, parseOptionsSection ( iter.second, constants, data_providers_map ) );
				}
				else if ( iter.first == Tags::OPTION )
				{
					const std::string &option_name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::OPTION::NAME );
					result.set<std::string> ( option_name, parseSingleOption ( iter.second, constants ) );
				}
				else if ( iter.first == Tags::PROVIDED_DATA )
				{
					const std::string &option_name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::PROVIDED_DATA::NAME );
					const std::string &data_provider_name = iter.second.get_child ( XMLATTR ).get<std::string> ( Attributes::PROVIDED_DATA::DATA_PROVIDER_NAME );
					if(data_providers_map == nullptr) throw NoDataProviderFound("Data provider not found while parsing option: '" + option_name + "'");
					const auto &iter = data_providers_map->find(data_provider_name);
					if(iter==data_providers_map->end()) throw NoDataProviderFound("Data provider not found while parsing option: '" + option_name + "'");
					result.set<Loader::IDataProvider*> ( option_name, iter->second );
				}
			}
			return result;
		}

		std::string OptionsParser::parseSingleOption ( const ptree &options_node, const ConstantsHolder *constants )
		{
			const std::string option_value = options_node.get_child ( XMLATTR ).get<std::string> ( Attributes::OPTION::VALUE );
			if ( constants != nullptr )
			{
				return constants->applyPlaceholderConstants ( option_value );
			}
			return option_value;
		}

	} /* namespace Loader */
} /* namespace UnknownEngine */
