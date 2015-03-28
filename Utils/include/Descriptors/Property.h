#pragma once

#include <Descriptors/IProperty.h>
#include <boost/lexical_cast.hpp>
#include <string>

#include <LogHelper.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T, IProperty::Optionality optionality>
		class Property : public IProperty
		{
			public:
				Property(){}
				Property(const T &default_value):
				value(default_value)
				{}

				Property(const Property<T, optionality> &prop):
				value(prop.value),
				is_explicitly_initialized(prop.is_explicitly_initialized)
				{}

				template<typename ...CArgs>
				Property(CArgs&& ...default_cargs):
				value(std::forward<CArgs>(default_cargs)...)
				{}
				
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
					try
					{
						value = boost::lexical_cast<T>(string_value_representation);
						is_explicitly_initialized = true;
					}
					catch(boost::bad_lexical_cast &e)
					{
						Core::LogHelper logger("Core.Utils.PropertiesParser", Core::LogSeverity::INFO);
						LOG_ERROR(logger, "Failed to initialized property from string: " + string_value_representation);
					}
					
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
				
				virtual bool isExplicitlyInitialized()
				{
					return is_explicitly_initialized;
				}

				virtual T* operator->()
				{
					return &value;
				}
				
			private:
				T value;
				bool is_explicitly_initialized = false;
		};
		
	}
}
