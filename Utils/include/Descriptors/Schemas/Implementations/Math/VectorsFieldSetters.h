#pragma once

#include <Vectors/Vector3.h>
#include <Vectors/Vector4.h>
#include <Descriptors/Schemas/DescriptorFieldSetter.h>
#include <CommonParsers/Vector3Parser.h>
#include <CommonParsers/Vector4Parser.h>

namespace UnknownEngine
{
	namespace Utils
	{
		
		template<>
		class DescriptorFieldSetter<Math::Vector3> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<Math::Vector3> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(Vector3Parser::parse(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<Math::Vector3> setter;
		};
		
		template<>
		class DescriptorFieldSetter<Math::Vector4> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<Math::Vector4> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(Vector4Parser::parse(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<Math::Vector4> setter;
		};
	}
}