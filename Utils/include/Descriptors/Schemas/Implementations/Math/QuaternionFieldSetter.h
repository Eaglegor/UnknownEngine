#pragma once

#include <Quaternion.h>
#include <Descriptors/Schemas/DescriptorFieldSetter.h>
#include <CommonParsers/QuaternionParser.h>

namespace UnknownEngine
{
	namespace Utils
	{
		
		template<>
		class DescriptorFieldSetter<Math::Quaternion> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<Math::Quaternion> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(QuaternionParser::parse(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<Math::Quaternion> setter;
		};
	}
}