#include <DescriptorParsersManager.h>

namespace UnknownEngine
{
	namespace Core
	{
		void DescriptorParsersManager::addComponentDescParser(const ComponentType &component_type, ComponentDescParser *parser)
		{
			if(component_desc_parsers.find(component_type) != component_desc_parsers.end()) throw ConflictingDescriptorParsersDetected("Conflicting component descriptor parsers detected");
			component_desc_parsers[component_type] = parser;
		}

		void DescriptorParsersManager::addDataProviderDescParser(const Loader::DataProviderType &data_provider_type, Loader::DataProviderDescParser *parser)
		{
			if(data_provider_desc_parsers.find(component_type) != data_provider_desc_parsers.end()) throw ConflictingDescriptorParsersDetected("Conflicting data provider descriptor parsers detected");
			data_provider_desc_parsers[component_type] = parser;
		}

		void DescriptorParsersManager::removeComponentDescParser(const ComponentType &component_type, ComponentDescParser *parser)
		{
			component_desc_parsers.erase(component_type);
		}

		void DescriptorParsersManager::removeDataProviderDescParser(const Loader::DataProviderType &data_provider_type,Loader::DataProviderDescParser *parser)
		{
			data_provider_desc_parsers.erase(data_provider_type);
		}

		DescriptorContainer &&DescriptorParsersManager::parseComponentDescriptor(const ComponentType &component_type, const Properties &options)
		{
			auto found_iter = component_desc_parsers.find(component_type);
			if(found_iter == component_desc_parsers.end()) throw NoSuitableDescriptorParserFound("Can't find suitable component descriptor parser");
			return std::move(found_iter->second.parse(component_type), options);
		}

		DescriptorContainer &&DescriptorParsersManager::parseDataProviderDescriptor(const Loader::DataProviderType &data_provider_type, const Properties &options)
		{
			auto found_iter = data_provider_desc_parsers.find(data_provider_type);
			if(found_iter == data_provider_desc_parsers.end()) throw NoSuitableDescriptorParserFound("Can't find suitable data provider descriptor parser");
			return std::move(found_iter->second.parse(data_provider_type), options);
		}

	}
}


