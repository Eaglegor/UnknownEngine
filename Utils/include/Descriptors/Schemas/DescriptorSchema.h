#pragma once

#include <Descriptors/Schemas/IDescriptorSchema.h>
#include <Descriptors/PropertiesTree/PropertiesTreeNode.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		class DescriptorSchema : public IDescriptorSchema<T>
		{
		public:
			
			DescriptorSchema() = delete;
			
			virtual void fillDescriptorFromPropertiesTree(const PropertiesTreeNode &properties, T& out_desc) = delete;
			
			virtual T createDefaultDescriptor() = delete;
			virtual T createDescriptor(const PropertiesTreeNode &properties) = delete;
			
			virtual PropertiesTreeNode convertDescriptorToPropertiesTree(const T& descriptor) = delete;
			virtual void writeDescriptorToPropertiesTree(const T& descriptor, PropertiesTreeNode &out_properties) = delete;
		};
	}
}