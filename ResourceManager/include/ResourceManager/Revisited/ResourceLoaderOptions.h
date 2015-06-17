#pragma once

#include <Descriptors/PropertiesTree/PropertiesTreeNode.h>
#include <Descriptors/Schemas/DescriptorSchema.h>
#include <memory>

namespace UnknownEngine
{
	namespace Resources
	{
		class ResourceLoaderOptions
		{
		public:
			ResourceLoaderOptions(const Utils::PropertiesTreeNode& options):
			properties_tree(options)
			{
			}

			template<typename T>
			T createDescriptor()
			{
				Utils::DescriptorSchema<T> schema;
				return schema.createDescriptor(properties_tree);
			}

		private:
			Utils::PropertiesTreeNode properties_tree;
		};
	}
}
