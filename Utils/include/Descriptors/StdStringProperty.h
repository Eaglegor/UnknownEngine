#pragma once

#include <Descriptors/Property.h>
#include <string>

namespace UnknownEngine
{
	namespace Utils
	{
		template<IProperty::Optionality optionality>
		class Property<std::string, optionality> : public IProperty
		{
		public:
			Property(){}
			Property(const std::string &default_value):
			value(default_value)
			{}
			
			Property(const Property<std::string, optionality> &prop):
			value(prop.value),
			is_explicitly_initialized(prop.is_explicitly_initialized)
			{}
			
			operator const std::string&() const
			{
				return value;
			}
			
			operator std::string&()
			{
				return value;
			}
			
			virtual IProperty& operator =(const std::string &string_value_representation) override
			{
				value = string_value_representation;
				is_explicitly_initialized = true;
				return *this;
			}
			
			std::string& get()
			{
				return value;
			}
			
			const std::string& get() const
			{
				return value;
			}
			
			virtual	operator std::string() override
			{
				return value;
			}
			
			virtual bool isValid()
			{
				if(optionality == OPTIONAL) return true;
				if(optionality == REQUIRED && is_explicitly_initialized) return true;
				return false;
			}
			
			virtual bool isExplicitlyInitialized()
			{
				return is_explicitly_initialized;
			}
			
			virtual std::string* operator->()
			{
				return &value;
			}
			
		private:
			std::string value;
			bool is_explicitly_initialized = false;
		};
		
	}
}
