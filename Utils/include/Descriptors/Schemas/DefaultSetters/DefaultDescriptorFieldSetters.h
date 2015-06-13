#pragma once

#include <Descriptors/Schemas/DescriptorFieldSetter.h>
#include <Descriptors/Schemas/DefaultSetters/DescriptorSetterFunction.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine
{
	namespace Utils
	{
		template<>
		class DescriptorFieldSetter<int> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<int> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<int>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<int> setter;
		};
		
		template<>
		class DescriptorFieldSetter<unsigned int> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<unsigned int> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<unsigned int>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<unsigned int> setter;
		};
		
		template<>
		class DescriptorFieldSetter<long> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<long> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<long>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<long> setter;
		};
		
		template<>
		class DescriptorFieldSetter<unsigned long> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<unsigned long> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<unsigned long>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<unsigned long> setter;
		};
		
		template<>
		class DescriptorFieldSetter<short> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<short> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<short>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<short> setter;
		};
		
		template<>
		class DescriptorFieldSetter<unsigned short> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<unsigned short> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<unsigned short>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<unsigned short> setter;
		};
		
		template<>
		class DescriptorFieldSetter<char> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<char> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<char>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<char> setter;
		};
		
		template<>
		class DescriptorFieldSetter<unsigned char> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<unsigned char> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<unsigned char>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<unsigned char> setter;
		};
		
		template<>
		class DescriptorFieldSetter<float> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<float> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<float>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<float> setter;
		};
		
		template<>
		class DescriptorFieldSetter<double> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<double> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(boost::lexical_cast<double>(value.getValue()));
			}
			
		private:
			DescriptorSetterFunction<double> setter;
		};
		
		template<>
		class DescriptorFieldSetter<bool> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<bool> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				try
				{
					setter(boost::lexical_cast<bool>(value.getValue()));
				}
				catch(const boost::bad_lexical_cast &e)
				{
					std::istringstream ss(value.getValue());
					bool b;
					ss >> std::boolalpha >> b;
					setter(b);
				}
			}
			
		private:
			DescriptorSetterFunction<bool> setter;
		};
		
		template<>
		class DescriptorFieldSetter<std::string> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<std::string> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				setter(value.getValue());
			}
			
		private:
			DescriptorSetterFunction<std::string> setter;
		};
		
	}
}