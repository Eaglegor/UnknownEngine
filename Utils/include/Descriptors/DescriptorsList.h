#pragma once

#include <Descriptors/IProperty.h>
#include <Descriptors/IDescriptorsList.h>
#include <boost/lexical_cast.hpp>
#include <vector>

namespace UnknownEngine
{
	namespace Utils
	{
		template <typename T, IProperty::Optionality optionality>
		class DescriptorsList : public IDescriptorsList
		{
			public:
				DescriptorsList():
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

				virtual IDescriptorsList<T> &operator =(const std::vector<Core::Properties> &props)
				{
					for(const Core::Properties &prop : props)
					{
						T desc = prop;
						properties_list.push_back(prop);
					}
					is_explicitly_initialized = true;
				}

			private:
				bool is_explicitly_initialized;
				std::vector< T > properties_list;
		};
	}
}
