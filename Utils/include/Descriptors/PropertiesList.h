#pragma once

#include <Descriptors/IProperty.h>
#include <Descriptors/IPropertiesList.h>
#include <Descriptors/RequiredProperty.h>
#include <boost/lexical_cast.hpp>
#include <vector>

namespace UnknownEngine
{
	namespace Utils
	{
		template <typename T, IProperty::Optionality optionality>
		class PropertiesList : public IPropertiesList<T>
		{
			public:
				PropertiesList():
				is_explicitly_initialized(false)
				{
				}

				virtual bool isValid()
				{
					return optionality == IProperty::OPTIONAL_PROPERTY || is_explicitly_initialized;
				}

				virtual const std::vector< T > & get()
				{
					return properties_list;
				}

				virtual IPropertiesList &operator =(const std::vector<std::string> &props)
				{
					for(const std::string &prop : props)
					{
						try
						{
							properties_list.push_back(boost::lexical_cast<T>(prop));
						}
						catch(const boost::bad_lexical_cast &e)
						{
							Core::LogHelper logger("Core.Utils.PropertiesParser", Core::LogSeverity::INFO);
							LOG_ERROR(logger, "Failed to initialized property from string: " + prop);
						}
					}
					is_explicitly_initialized = true;
				}

			private:
				bool is_explicitly_initialized;
				std::vector< T > properties_list;
		};
	}
}
