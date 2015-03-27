#pragma once

#include <Descriptors/IProperty.h>
#include <boost/lexical_cast.hpp>
#include <string>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T, IProperty::Optionality optionality>
		class Property : public IProperty
		{
			public:
				Property(){}
				Property(const T &value):value(value){}

				Property(const Property<T, optionality> &prop):value(prop.value){}

				operator const T&() const
				{
					return value;
				}

				operator T&()
				{
					return value;
				}
				
				Property<T, optionality>& operator =(const T& value)
				{
					this->value = value;
					return *this;
				}
				
				Property<T, optionality>& operator =(const Property<T, optionality> &prop)
				{
					this->value = prop.value;
					return *this;
				}
				
				virtual IProperty& operator =(const std::string &string_value_representation) override
				{
					value = boost::lexical_cast<T>(string_value_representation);
					is_explicitly_initialized = true;
					return *this;
				}

				T& get()
				{
					return value;
				}
				
				const T& get() const
				{
					return value;
				}
				
				virtual	operator std::string() override
				{
					return boost::lexical_cast<std::string>(value);
				}

				virtual bool isValid()
				{
					if(optionality == OPTIONAL) return true;
					if(optionality == REQUIRED && is_explicitly_initialized) return true;
					return false;
				}

			private:
				bool is_explicitly_initialized = false;
				T value;
		};
		
		template<IProperty::Optionality optionality>
		class Property<std::string, optionality> : public IProperty
		{
			public:
				Property(){}
				Property(const std::string &value):value(value){}

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

			private:
				bool is_explicitly_initialized = false;
				std::string value;
		};
		
	}
}
