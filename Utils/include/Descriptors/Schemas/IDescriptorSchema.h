#pragma once

#include <Descriptors/PropertiesTree/PropertiesTreeNode.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		class IDescriptorSchema
		{
		public:
			virtual ~IDescriptorSchema(){}
			
			virtual void fillDescriptorFromPropertiesTree(const PropertiesTreeNode &properties, T& out_desc) = 0;
			
			virtual T createDefaultDescriptor() = 0;
			virtual T createDescriptor(const PropertiesTreeNode &properties) = 0;
			
			virtual PropertiesTreeNode convertDescriptorToPropertiesTree(const T& descriptor) = 0;
			virtual void writeDescriptorToPropertiesTree(const T& descriptor, PropertiesTreeNode &out_properties) = 0;
		};
	}
}