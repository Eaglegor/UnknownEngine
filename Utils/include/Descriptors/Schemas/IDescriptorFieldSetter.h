#pragma once

#include <Descriptors/PropertiesTree/PropertiesTreeNode.h>

namespace UnknownEngine
{
	namespace Utils
	{
		class IDescriptorFieldSetter
		{
		public:
			virtual ~IDescriptorFieldSetter(){}
			virtual void setValue(const PropertiesTreeNode& value) = 0;
		};
	}
}