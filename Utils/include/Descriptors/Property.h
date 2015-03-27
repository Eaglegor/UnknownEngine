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
				Property(T &&value):value(value){}

				operator T()
				{
					return value;
				}

				virtual IProperty& operator =(const char *string_value_representation) override
				{
					value = boost::lexical_cast<T>(string_value_representation);
					is_explicitly_initialized = true;
					return *this;
				}

				virtual operator std::string() override
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
	}
}
